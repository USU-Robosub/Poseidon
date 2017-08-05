#ifndef ACTUATOR_LOCK_H
#define ACTUATOR_LOCK_H

#include <map>
#include <string>
#include "Node.hpp"

typedef std::string (*UUIDgenerator)(void);

class ActuatorLock : public Node{
public:
  ActuatorLock(UUIDgenerator generateUUID) : generateUUID(generateUUID) {}
  void update(IHub* hub);
  void process(IHub* hub, json message);
private:
  std::map<std::string, std::string> locks;
  UUIDgenerator generateUUID;
};

#endif
