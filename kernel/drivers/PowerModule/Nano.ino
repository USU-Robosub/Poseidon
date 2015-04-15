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
  
  // pins 1-8 set as output
  // used for relay controls to turn on and off the thrusters
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  // used to measure current or voltage of the power supply
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  // debugging LED
  pinMode(13, OUTPUT);
  
  // reset registers with reset values
  _map_[0x00] = 0x11;
  _map_[0x01] = 0x00;
  _map_[0x02] = 0x00;
  setPins();
}

void loop()
{
  delay(100);
  if(flg)
  { 
    // [             -- REGISTER MAP --               ]
    // 0: version  1: status   2: relay brd  3: lights
    // 4: Amps AH  5: Amps AL  6: Amps BH    7: Amps BL
    // 8: Amps CH  9: Amps CL  A: Amps DH    B: Amps DL
    // C: rsrv     D: addr     E: rsrv       F: rsrv
    
    // if writing to the device and address is within range
    if(wrt && addr < CMAP)
    {
      digitalWrite(13, HIGH);
      switch(addr)
      {
        // set relay state
        case 0x02:
          _map_[0x02] = data;
          setPins();
          break;
        // set headlights
        case 0x03:
          _map_[0x03] = data;
          break;
        // set read register
        case 0x0D:
          _map_[0x0D] = data & (CMAP-1);
          break;
        default: break;
      }
    }
    
    flg = 0;
    _map_[0x01] = 0; // status = not updated
  }
  // else continue updating registers
  else
  {
    // - update registers -
    // NOTE: the lighting isn't necessary but does add for
    // a cool affect! Delays also shouldn't need to be too
    // long but reasonable to help with data collection.
    _map_[0x01] = 0; // status = not updated
    digitalWrite(13, LOW);
    delay(300);      // pause for a second
    
    int amp = 0;
    amp = analogRead(A0);
    _map_[0x05] = (uint8_t)amp; _map_[0x04] = (uint8_t)(amp >> 8);
    amp = analogRead(A1);
    _map_[0x07] = (uint8_t)amp; _map_[0x06] = (uint8_t)(amp >> 8);
    amp = analogRead(A2);
    _map_[0x09] = (uint8_t)amp; _map_[0x08] = (uint8_t)(amp >> 8);
    
    _map_[0x01] = 1; // status = updated
    digitalWrite(13, HIGH);
  }
  
  // if status is ready, light LED, otherwise turn it off
  if(_map_[0x01])
  {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}

// function that executes whenever data is received on i2c
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  addr = Wire.read();
  // if there is still data being transmitted
  // the master is trying to write to the device
  // NOTE: this check may not be necessary since the device
  // is always written to and never durring read.
  if(Wire.available())
  {
    wrt = 1;
    data = Wire.read();
  }
  else { wrt = 0; }
  flg = 1;
}

// function that executes whenever data is requested on i2c
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write(_map_[_map_[0x0D]]);
}

// set relay pins 3-10
void setPins() {
  int off = 3;
  for(int i = 0; i < 8; i++) {
    if((_map_[0x02] >> i) & 1)
    {
      digitalWrite(i+off, LOW);
    }
    else {
      digitalWrite(i+off, HIGH);
    }
  } 
}
