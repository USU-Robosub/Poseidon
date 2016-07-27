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



volatile int bufn,obufn;
const uint16_t BUF_SIZE     = 1024;   // 340 samples * 3 channels = ~1024
const uint16_t BUF_DIM_SIZE = 2;
uint16_t buf[BUF_DIM_SIZE][BUF_SIZE]; // 4 buffers of 255 samples
int ADC_Stage               = 0;      // 0 - off; 1 - active/busy; 2 - ready;
int samples                 = 20;     // default 20 sample intervals
float freq                  = 25000;  // default 25kHz
bool sfound                 = false;
int threshold               = 1228;   // 80% of 4095 (max value)
int time1 = 0, time2 = 0, time3 = 0;  // time intervals

const uint8_t DRDY = 24, ENDRX = 27;
const uint8_t ACTIVE_SENSOR = 0;
const uint8_t SET_THRESH = 2;
const uint8_t SET_FREQ = 1;



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



void transform(Complex* input, int start, int length, float & res, float & maxMag)
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



bool helper_Algorithm(Complex* data, int start, int length)
{
    float test = 0, result = 0;
    transform(data, start, length, result, test);
    test = test == 0 ? 1 : test * 0.8F;
    return result >= test;
}



void algorithm(ChannelBuffers buffers)
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

    do
    {
        if (ch1_nfound)
        {
            if (helper_Algorithm(buffers.channelA, cha_off, samples))
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
            if (helper_Algorithm(buffers.channelB, chb_off, samples))
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
            if (helper_Algorithm(buffers.channelC, chc_off, samples))
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
            if (ch1_nfound) time1++;
            if (ch2_nfound) time2++;
            if (ch3_nfound) time3++;
        }

    } while (ch1_nfound || ch2_nfound || ch3_nfound);

    // one more pass for convinience
    // (if one or two were found but the rest were not by the end of the buffer,
    // this will automatically suggest maximum time difference)
    if (found)
    {
        if (ch1_nfound) time1++;
        if (ch2_nfound) time2++;
        if (ch3_nfound) time3++;
    }

    ADC_Stage++;
}



ChannelBuffers sortDMA()
{
    ChannelBuffers buffers(BUF_SIZE * BUF_DIM_SIZE / 3);

    int i = 0, j;
    int a = 0, b = 0, c = 0;

    do {
        for (j = 0; j < BUF_SIZE; j++)
        {
            uint16_t value = buf[obufn][j];

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
    } while (i < BUF_DIM_SIZE);

    return buffers;
} 



const int CENTER_LINE = 2048; // ~4097 / 2

void testForSound() {
  for(int i = 0; i < BUF_SIZE; i++) {
    if(buf[obufn][i] >= (CENTER_LINE + threshold) ||
       buf[obufn][i] <= (CENTER_LINE - threshold)) {
      sfound = true;
      break;
    }
  }
  obufn=(obufn+1) % BUF_DIM_SIZE;
}



void softReset() {
  ADC->ADC_CR = 1;                  // software reset
  sfound      = false;
}



void ADC_Handler() {
  int f=ADC->ADC_ISR;

  // The Receive Counter Register has reached 0
  // since the last write in ADC_RCR or ADC_RNCR
  if (f&(1<<ENDRX)){
    if(!sfound) {
      bufn = (bufn + 1) % BUF_DIM_SIZE;
      ADC->ADC_RNPR=(uint32_t)buf[bufn];
      ADC->ADC_RNCR=BUF_SIZE;
      testForSound();
    }
    else {
      softReset();
      ChannelBuffers buffers = sortDMA();
      algorithm(buffers);
    }
  }
}



class HydroController : public IController {
public:  
  HydroController() {
    kill();
  }



  void configure() {
    ADC_Stage = 1;

    pmc_enable_periph_clk(ID_ADC);
    adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST);
    ADC->ADC_MR |=0x80;               // free running - 1000 0000
    ADC->ADC_CHER=0x00E0;             // channel enable register - A0, A1, & A2
    ADC->ADC_CHDR=~0x00E0;            // channel disable register
  
    NVIC_EnableIRQ(ADC_IRQn);
    ADC->ADC_IDR  =~(1<<ENDRX);       // F7 FF FF FF - end of receive buffer interrupt disable
    ADC->ADC_IER  = (1<<ENDRX);       // 08 00 00 00 - end of receive buffer interrupt enable
    ADC->ADC_RPR  =(uint32_t)buf[0];  // DMA buffer - receive pointer register
    ADC->ADC_RCR  =BUF_SIZE;          // receive counter register
    ADC->ADC_RNPR =(uint32_t)buf[1];  // next DMA buffer - receive next pointer register
    ADC->ADC_RNCR =BUF_SIZE;          // receive next counter register
    ADC->ADC_EMR |= (1<<24);          // extended mode register - tag data
    
    bufn = obufn = 0;
    ADC->ADC_PTCR=1;                  // transfer control register
    ADC->ADC_CR=2;                    // start
  }



  void setFrequency(uint16_t value) {
    freq = static_cast<float>(value);
    samples = (int)(500000.0 / freq);
  }



  void printData() {
    Serial.print("{\"State\":");
    if(ADC_Stage == 0) {
      Serial.print("\"activated\"");
      configure();
    }
    else if(ADC_Stage == 1) {
      Serial.print("\"busy\"");
    }
    else {
      Serial.print("\"data\"");
      ADC_Stage = 0;
    }
    Serial.print(",\"A\":\"");
    Serial.print(time1);
    Serial.print("\",\"B\":\"");
    Serial.print(time2);
    Serial.print("\",\"C\":\"");
    Serial.print(time3);
    Serial.println("\"}");
  }
  


  void execute() {
    while(!Serial.available());
    uint8_t process = Serial.read();

    if(process == ACTIVE_SENSOR) {
      printData();
    }
    else if(process == SET_FREQ) {
      uint16_t value = readShort();
      setFrequency(value);
    }
    else if(process == SET_THRESH) {
      threshold = (int)readShort();
    }
  }



  void kill() {
    softReset();
    ADC_Stage = 0;
  }
};