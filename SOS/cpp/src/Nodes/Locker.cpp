#include "Locker.hpp"
#include <iostream>

void Locker::update(IHub*) { }

void Locker::process(IHub* hub, std::string* connection, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("getLock"))                   lock(hub, connection, message);
    else if(message->matchesType("releaseLock"))            unlock(hub, connection, message);
  }
}

void Locker::lock(IHub* hub, std::string* connection, Message* message){
  if(message->getData()["node"].is_string()){
    std::string lockedNodeName = message->getData()["node"];
    if(locks.find(lockedNodeName) == locks.end()){
      std::string key = locks[lockedNodeName] = generateUUID();
      hub->send("LOCAL", Message().to(lockedNodeName).ofType("lock").from(nodeName).withData(json({
        {"key", key}
      })));
      hub->send(*connection, Message().to(message->getSender()).ofType("grantLock").from(nodeName).withData(json({
        {"key", key},
        {"node", lockedNodeName}
      })));
    }else{
      hub->send(*connection, Message().to(message->getSender()).ofType("rejectLock").from(nodeName).withData(json({
        {"node", lockedNodeName}
      })));
    }
  }
}

void Locker::unlock(IHub* hub, std::string* connection, Message* message){
  if(message->getData()["node"].is_string() && message->getData()["key"].is_string()){
    std::string lockedNodeName = message->getData()["node"];
    std::string key = message->getData()["key"];
    if(locks.find(lockedNodeName) != locks.end() && locks[lockedNodeName] == key){
      hub->send("LOCAL", Message().to(lockedNodeName).ofType("unlock").from(nodeName).withData(json({
        {"key", key}
      })));
      locks.erase(lockedNodeName);
    }
  }
}
