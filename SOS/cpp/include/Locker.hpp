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
  void process(IHub* hub, std::string* connection, Message* message);
private:
  void lock(IHub* hub, std::string* connection, Message* message);
  void unlock(IHub* hub, std::string* connection, Message* message);
  void forceUnlockAll(IHub* hub, std::string* connection, Message* message);
  std::map<std::string, std::string> locks;
  UUIDgenerator generateUUID;
};

#endif
