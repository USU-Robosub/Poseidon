#ifndef ACTUATOR_LOCK_H
#define ACTUATOR_LOCK_H

#include "Node.hpp"

class ActuatorLock : public Node{
public:
  void update(Hub* hub);
  void process(Hub* hub, json::object data);
};

#endif
