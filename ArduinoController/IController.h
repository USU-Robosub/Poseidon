#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "Arduino.h"
#include "SerialTools.h"
#include "PinMap.h"

class IController {
 public:
  virtual void execute() = 0;
  virtual void kill() = 0;
};

#endif
