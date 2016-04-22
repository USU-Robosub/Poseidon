#ifndef ITHRUSTER_H
#define ITHRUSTER_H

#include "Arduino.h"

class IController {
 public:
  virtual void execute() = 0;
  virtual void kill() = 0;
};

#endif
