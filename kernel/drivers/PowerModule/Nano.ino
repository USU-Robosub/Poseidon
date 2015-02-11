#include <Wire.h>
#include "stdint.h"

// pins A4:DAT & A5:CLK
#define CMAP 0x10

uint8_t addr = 0;
uint8_t data = 0;
int flg = 0, wrt = 0;

uint8_t _map_[CMAP];

void setup()
{
  Wire.begin(0x03);             // join i2c bus with address 0x02
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  //Serial.begin(115200);         // start serial for output
  
  // pins 0-7 set as output
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  pinMode(13, OUTPUT);
  
  _map_[0x00] = 0x11;
  _map_[0x01] = 0x00;
  _map_[0x02] = 0x00;
  setPins(_map_[0x02]);
}

void loop()
{
  delay(100);
  if(flg)
  { 
    // 0: version  1: status   2: thrusters  3: lights
    // 4: Amps AH  5: Amps AL  6: Amps BH    7: Amps BL
    // 8: Amps CH  9: Amps CL  A: Amps DH    B: Amps DL
    // C: rsrv     D: addr     E: rsrv       F: rsrv
    
    if(wrt && addr < CMAP)
    {
      digitalWrite(13, HIGH);
      switch(addr)
      {
        case 0x02:
          _map_[0x02] = data;
          setPins(_map_[0x02]);
          break;
        case 0x03:
          _map_[0x03] = data;
          // prototype: pins 8 - 13
          break;
        case 0x0D:
          _map_[0x0D] = data & (CMAP-1);
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
    digitalWrite(13, LOW);
    delay(300);
    
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
    digitalWrite(13, HIGH);
  }
  
  if(_map_[0x01])
  {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  addr = Wire.read();
  if(Wire.available())
  {
    wrt = 1;
    data = Wire.read();
  }
  else { wrt = 0; }
  flg = 1;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write(_map_[_map_[0x0D]]);
}

// set relay access pins
void setPins(uint8_t dat) {
  for(int i = 0; i < 8; i++) {
    if((dat >> i) & 1)
    {
      digitalWrite(i+2, LOW);
    }
    else {
      digitalWrite(i+2, HIGH);
    }
  } 
}
