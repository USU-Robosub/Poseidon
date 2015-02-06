#include <Wire.h>
#include "stdint.h"

// pins A4:DAT & A5:CLK
#define CMAP 12

uint8_t addr = 0;
uint8_t data = 0;
int flg = 0, wrt = 0;
uint8_t dout = 0;

uint8_t _map_[CMAP];

void setup()
{
  Wire.begin(0x02);             // join i2c bus with address 0x02
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  //Serial.begin(115200);         // start serial for output
  
  DDRD = 0xFF; // pins 0-7 set as output
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  _map_[0x00] = 0x11;
}

void loop()
{
  delay(1);
  if(flg)
  { 
    // manipulate registers
    if(!wrt && addr < CMAP)
    {
      // 0: version  1: status   2: thrusters  3: lights
      // 4: Amps AH  5: Amps AL  6: Amps BH    7: Amps BL
      // 8: Amps CH  9: Amps CL 10: Amps DH   11: Amps DL
      dout = _map_[addr];
    }
    else if(wrt && addr < CMAP)
    {
      switch(addr)
      {
        case 0x02:
          _map_[0x02] = data;
          PORTD = _map_[0x02];
          break;
        case 0x03:
          _map_[0x03] = data;
          // prototype: pins 8 - 13
          break;
        default: break;
      }
    }
    
    flg = 0;
    _map_[0x01] = 0; // not updated
  }
  else
  {
    // update registers
    _map_[0x01] = 0; // not updated
    
    int amp = 0;
    amp = analogRead(A0);
    _map_[0x05] = (uint8_t)amp; _map_[0x04] = (uint8_t)(amp >> 8);
    amp = analogRead(A1);
    _map_[0x07] = (uint8_t)amp; _map_[0x06] = (uint8_t)(amp >> 8);
    amp = analogRead(A2);
    _map_[0x09] = (uint8_t)amp; _map_[0x08] = (uint8_t)(amp >> 8);
    amp = analogRead(A3);
    _map_[0x0B] = (uint8_t)amp; _map_[0x0A] = (uint8_t)(amp >> 8);
    
    _map_[0x01] = 1; // updated
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
    addr = Wire.read();
    if(Wire.available())
    {
      wrt = 0;
      data = Wire.read();
    }
    else { wrt = 1; }
    flg = 1;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write(dout);
}
