#ifndef ACTUATOR_LOCK_H
#define ACTUATOR_LOCK_H

#include <map>
#include <string>
#include "Node.hpp"

typedef std::string (*UUIDgenerator)(void);

class ActuatorLock : public Node{
public:
  ActuatorLock(UUIDgenerator generateUUID) : generateUUID(generateUUID) {}
  void setName(std::string name);
  void update(IHub* hub);
  void process(IHub* hub, json message);
private:
  std::string generateAPPLY_LOCK(std::string key);
  std::string generateGRANT_LOCK(std::string hub, std::string lockedNode, std::string key);
  std::string generateREJECT_LOCK(std::string hub, std::string triedNode);
  std::string generateREMOVE_LOCK(std::string key);
  std::string name;
  std::map<std::string, std::string> locks;
  UUIDgenerator generateUUID;
};

#endif
