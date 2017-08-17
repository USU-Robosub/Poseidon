#include "Locker.hpp"
#include <iostream>

void Locker::update(IHub* hub){
  // do nothing
}

void Locker::process(IHub* hub, std::string* connection, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("LOCK"))                   lock(hub, connection, message);
    else if(message->matchesType("UNLOCK"))            unlock(hub, connection, message);
    else if(message->matchesType("FORCE_UNLOCK_ALL"))  forceUnlockAll(hub, connection, message);
  }
}

void Locker::lock(IHub* hub, std::string* connection, Message* message){
  std::string lockedNodeName = message->getData()["node"];
  if(locks.find(lockedNodeName) == locks.end()){
    std::string key = locks[lockedNodeName] = generateUUID();
    hub->send("LOCAL", Message(lockedNodeName, "APPLY_LOCK", nodeName, json({
      {"key", key}
    })));
    hub->send(*connection, Message(message->getSender(), "GRANT_LOCK", nodeName, json({
      {"key", key},
      {"node", lockedNodeName}
    })));
  }else{
    hub->send(*connection, Message(message->getSender(), "REJECT_LOCK", nodeName, json({
      {"node", lockedNodeName}
    })));
  }
}

void Locker::unlock(IHub* hub, std::string* connection, Message* message){
  std::string lockedNodeName = message->getData()["node"];
  std::string key = message->getData()["key"];
  if(locks.find(lockedNodeName) != locks.end() && locks[lockedNodeName] == key){
    hub->send("LOCAL", Message(lockedNodeName, "REMOVE_LOCK", nodeName, json({
      {"key", key}
    })));
    locks.erase(lockedNodeName);
  }
}

void Locker::forceUnlockAll(IHub* hub, std::string* connection, Message* message){
  for (auto& lock : locks){
    std::string const& lockedNodeName = lock.first;
    std::string const& key = lock.second;
    hub->send("LOCAL", Message(lockedNodeName, "REMOVE_LOCK", nodeName, json({
      {"key", key}
    })));
  }
  locks.clear();
}
