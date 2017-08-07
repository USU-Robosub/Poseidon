#ifndef ACTUATOR_LOCK_H
#define ACTUATOR_LOCK_H

#include <map>
#include <vector>
#include <string>
#include "Node.hpp"

typedef std::string (*UUIDgenerator)(void);

class Locker : public Node{
public:
  Locker(UUIDgenerator generateUUID) : generateUUID(generateUUID) {}
  void update(IHub* hub);
  void process(IHub* hub, std::string connection, json message);
private:
  std::string generateAPPLY_LOCK(std::string target, std::string key);
  std::string generateGRANT_LOCK(std::string target, std::string node, std::string key);
  std::string generateREJECT_LOCK(std::string target, std::string node);
  std::string generateREMOVE_LOCK(std::string target, std::string key);
  std::map<std::string, std::string> locks;
  UUIDgenerator generateUUID;
};

#endif
