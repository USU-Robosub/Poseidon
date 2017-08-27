#ifndef DUMMY_H
#define DUMMY_H

#include "IController.h"

class Dummy : public IController {
public:
  Dummy() {}
  void execute() {}
  void kill() {}
};

#endif
