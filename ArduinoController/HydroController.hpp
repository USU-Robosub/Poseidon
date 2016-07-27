#undef HID_ENABLED

// Arduino Due ADC->DMA->USB 1MSPS
// by stimmer
// from http://forum.arduino.cc/index.php?topic=137635.msg1136315#msg1136315
// Input: Analog in A0
// Output: Raw stream of uint16_t in range 0-4095 on Native USB Serial/ACM

// on linux, to stop the OS cooking your data: 
// stty -F /dev/ttyACM0 raw -iexten -echo -echoe -echok -echoctl -echoke -onlcr

#include "IController.h"
#include "Complex.h"


typedef struct TimeDiff {
  int A, B, C;
} TimeDiff;

int samples                 = 20;     // default 20 sample intervals, default 25kHz
int threshold               = 1228;   // 80% of 4095 (max value)

const uint8_t DRDY = 24, ENDRX = 27;
const uint16_t BUF_SIZE     = 1024;   // 340 samples * 3 channels = ~1024
const uint8_t BUF_DIM_SIZE = 3;
const uint8_t MAIN_BUF_DIM = 2;
volatile int bufn,obufn;
uint16_t buf[BUF_DIM_SIZE][BUF_SIZE];
uint16_t mbuf[MAIN_BUF_DIM][BUF_SIZE];
uint8_t hc_flags = 0;
uint8_t BUFFER_STAGE = 1;
uint8_t DATA_IN_USE = 1<<2;



// tests the current buffer block for sound
const int CENTER_LINE = 2048; // ~4097 / 2
void HC_sound_test() {
  for(int i = 0; i < BUF_SIZE; i++) {
    if(buf[obufn][i] >= (CENTER_LINE + threshold) ||
       buf[obufn][i] <= (CENTER_LINE - threshold)) {
      // set next stage
      hc_flags |= BUFFER_STAGE;
      break;
    }
  }
  obufn=(obufn+1) % BUF_DIM_SIZE;
}



// starts the interrupt service routine (ISR) for the
// analog to digital (ADC) converter
void HC_start() {
  pmc_enable_periph_clk(ID_ADC);
  adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST);
  ADC->ADC_CHER=0x00E0;             // channel enable register - A0, A1, & A2
  ADC->ADC_CHDR=~0x00E0;            // channel disable register
  
  ADC->ADC_MR |=0x80;               // free running - 1000 0000
  NVIC_EnableIRQ(ADC_IRQn);
  ADC->ADC_IDR  =~(1<<ENDRX);       // F7 FF FF FF - end of receive buffer interrupt disable
  ADC->ADC_IER  = (1<<ENDRX);       // 08 00 00 00 - end of receive buffer interrupt enable
  
  ADC->ADC_RPR  =(uint32_t)buf[0];  // DMA buffer - receive pointer register
  ADC->ADC_RCR  =BUF_SIZE;          // receive counter register
//  ADC->ADC_RNPR =(uint32_t)buf[1];  // next DMA buffer - receive next pointer register
//  ADC->ADC_RNCR =BUF_SIZE;          // receive next counter register
  ADC->ADC_EMR |= (1<<24);          // extended mode register - tag data
  
  bufn = obufn = 0;
  ADC->ADC_PTCR=1;                  // transfer control register
  ADC->ADC_CR=2;                    // start
}



// stops the ISR for the ADC, preventing future interrupts
void HC_stop() {
  ADC->ADC_CR = 1;                  // software reset
}



// ADC ISR function callback
void ADC_Handler() {
  int f=ADC->ADC_ISR;
  int i, j, k;

  if (f&(1<<ENDRX)){
    // set next buffer to fill
    bufn = (bufn + 1) % BUF_DIM_SIZE;
    ADC->ADC_RNPR=(uint32_t)buf[bufn];
    ADC->ADC_RNCR=BUF_SIZE;

    // apply operations on newly filled buffer
    // based on the analyzing stage
    if((hc_flags&BUFFER_STAGE) == 0) {
      // testing each buffer for sound
      BC_sound_test();
    }
    if((hc_flags&BUFFER_STATE) == 1) {
      // buffer 2 is finished (buffer 3 is now in queue)
      if((hc_flags&DATA_IN_USE) == 0) {
        // copy buffer to main thread
        k = (obufn + BUF_DIM_SIZE - 1) % BUF_DIM_SIZE; // get start index of buffer to copy
        for(i = 0; i < MAIN_BUF_DIM; i++) {
          for(j = 0; j < BUF_SIZE; j++) {
            mbuf[i][j] = buf[k][j];
          }
          k = (k + 1) % BUF_DIM_SIZE;
        }
      }
      hc_flags ^= ~BUFFER_STATE;
    }
  }
}



class ChannelBuffers {
public:
  ChannelBuffers(int bufSize) {
    size = bufSize;
    channelA = new Complex[size];
    channelB = new Complex[size];
    channelC = new Complex[size];
  }

  ~ChannelBuffers() {
    delete channelA;
    delete channelB;
    delete channelC;
  }
  
  Complex * channelA;
  Complex * channelB;
  Complex * channelC;
  int size;
};



// finds frequency information based on input properties
void HC_transform(Complex* input, int start, int length, float & res, float & maxMag)
{
    int N = length;
    float _res_ = 0;
    maxMag = 0;

    float arg = -2.0F * 3.141592653F / (float)N;
    for (int n = 0; n < N; n++)
    {
        Complex output;
        for (int k = 0; k < N; k++) {
          Complex * polar = Complex::fromPolarCoordinates(1, arg * (float)n * (float)k);
          polar->multiply(input[k + start]);
          output.add(*polar);
        }

        if (output.Magnitude() > maxMag)
            maxMag = (float)output.Magnitude();

        if (n == 0)
            _res_ = (float)output.Magnitude();
    }

    res = _res_;
}



bool HC_time_helper(Complex* data, int start, int length)
{
    float test = 0, result = 0;
    HC_transform(data, start, length, result, test);
    test = test == 0 ? 1 : test * 0.8F;
    return result >= test;
}



// performs a time difference offset calculation which will later be used
// to triangulate distance and direction
TimeDiff HC_time_algorithm(ChannelBuffers buffers)
{
    time1 = 0;
    time2 = 0;
    time3 = 0;
    int cha_off = 0,
        chb_off = 0,
        chc_off = 0;
    bool
        found      = false,
        ch1_nfound = true,
        ch2_nfound = true,
        ch3_nfound = true;
    TimeDiff diff;
    diff.A = 0;
    diff.B = 0;
    diff.C = 0;

    do
    {
        if (ch1_nfound)
        {
            if (HC_time_helper(buffers.channelA, cha_off, samples))
            {
                found      = true;
                ch1_nfound = false;
            }
            cha_off += samples;
            // handle overflow
            if (ch1_nfound && cha_off + samples >= buffers.size)
                break;
        }
        if (ch2_nfound)
        {
            if (HC_time_helper(buffers.channelB, chb_off, samples))
            {
                found      = true;
                ch2_nfound = false;
            }
            chb_off += samples;
            if (ch2_nfound && chb_off + samples >= buffers.size)
                break;
        }
        if (ch3_nfound)
        {
            if (HC_time_helper(buffers.channelC, chc_off, samples))
            {
                found      = true;
                ch3_nfound = false;
            }
            chc_off += samples;
            if (ch3_nfound && chc_off + samples >= buffers.size)
                break;
        }

        if (found)
        {
            if (ch1_nfound) diff.A++;
            if (ch2_nfound) diff.B++;
            if (ch3_nfound) diff.C++;
        }

    } while (ch1_nfound || ch2_nfound || ch3_nfound);

    // one more pass for convinience
    // (if one or two were found but the rest were not by the end of the buffer,
    // this will automatically suggest maximum time difference)
    if (found)
    {
        if (ch1_nfound) diff.A++;
        if (ch2_nfound) diff.B++;
        if (ch3_nfound) diff.C++;
    }

    return diff;
}



// right now the buffers contain randomly ordered data from all 3 ADC channels
// we need to sort them into individual channels for easier processing
ChannelBuffers HC_sort_dma()
{
    ChannelBuffers buffers(BUF_SIZE * BUF_DIM_SIZE / 3);

    int i = 0, j;
    int a = 0, b = 0, c = 0;

    do {
        for (j = 0; j < BUF_SIZE; j++)
        {
            uint16_t value = mbuf[i][j];

            uint8_t tag = (uint8_t)(value >> 12);
            Complex cval((value & 0x0FFF) / (float)0x0FFF, 0);

            if (tag == 5 && c < buffers.size)
            {
                buffers.channelC[c] = cval;
                c++;
            }
            else if (tag == 6 && b < buffers.size)
            {
                buffers.channelB[b] = cval;
                b++;
            }
            else if (tag == 7 && a < buffers.size)
            {
                buffers.channelA[a] = cval;
                a++;
            }
        }

        i++;
        obufn = (obufn + 1) % BUF_DIM_SIZE;
    } while (i < MAIN_BUF_DIM);

    return buffers;
}



TimeDiff HC_process_data() {
  ChannelBuffers buffers = HC_sort_dma();
  return HC_time_algorithm(buffers);
}



class HydroController : public IController {
public:  
  HydroController() {
    kill();
  }
  


  void execute() {
    while(!Serial.available());
    uint8_t action = Serial.read();
    if(action == 0) {
      HC_start();
    }
    else if() {
      TimeDiff res = HC_process_data();
      Serial.print("{\"F\":\"");
      Serial.print(res.A);
      Serial.print("\",\"L\":\"");
      Serial.print(res.B);
      Serial.print("\",\"R\":\"");
      Serial.print(res.C);
      Serial.print("\"}");
    }
    else if(action == 2) {
      HC_stop();
    }
    else if(action == 3) {
      samples = Serial.read();
    }
    else if(action == 4) {
      threshold = readShort();
    }
  }



  void kill() {
    int i = 0, j = 0;
    // zero the main buffer
    for(; i < MAIN_BUF_DIM; i++) {
      for(; j < BUF_SIZE; j++) {
        mbuf[i][j] = 0;
      }
    }
  }
};


