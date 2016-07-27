#ifndef ITHRUSTER_H
#define ITHRUSTER_H

#include "Arduino.h"

uint16_t readShort() {
  while(Serial.available() < 2) {}
  return Serial.read() << 8 | Serial.read();
}

class IController {
 public:
  virtual void execute() = 0;
  virtual void kill() = 0;
};

#endif
