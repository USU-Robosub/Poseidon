#include "Locker.hpp"
#include <iostream>

void Locker::setName(std::string name){
  this->name = name;
}

void Locker::update(IHub* hub){
  // do nothing
}

void Locker::process(IHub* hub, json message){
  auto from = message["from"];
  auto to = message["to"];
  auto request = message["request"];
  if(request["type"].get<std::string>() == "LOCK"){
    std::string key = generateUUID();
    std::string actuator = request["hub"].get<std::string>() + "|" + request["node"].get<std::string>();
    if(locks.find(actuator) == locks.end()){
      locks.insert(std::pair<std::string,std::string>(actuator, key));
      hub->send(name, request["hub"], request["node"], generateAPPLY_LOCK(key));
      hub->send(name, from["hub"], from["node"], generateGRANT_LOCK(request["hub"], request["node"], key));
    }else{
      hub->send(name, from["hub"], from["node"], generateREJECT_LOCK(request["hub"], request["node"]));
    }
  }else if(request["type"] == "UNLOCK"){
    std::string key = request["lock"];
    std::string actuator = request["hub"].get<std::string>() + "|" + request["node"].get<std::string>();
    if(locks.find(actuator) != locks.end() && locks[actuator] == key){
      locks.erase(actuator);
      hub->send(name, request["hub"], request["node"], generateREMOVE_LOCK(key));
    }
  }else{
    //hub->error("Lock command invalid");
  }
}

std::string Locker::generateAPPLY_LOCK(std::string key) {
  return json({
    {"type", "APPLY_LOCK"},
    {"lock", key}
  }).dump();
}

std::string Locker::generateGRANT_LOCK(std::string hub, std::string lockedNode, std::string key){
  return json({
    {"type", "GRANT_LOCK"},
    {"hub", hub},
    {"node", lockedNode},
    {"lock", key},
  }).dump();
}

std::string Locker::generateREJECT_LOCK(std::string hub, std::string triedNode){
  return json({
    {"type", "REJECT_LOCK"},
    {"hub", hub},
    {"node", triedNode},
  }).dump();
}


std::string Locker::generateREMOVE_LOCK(std::string key){
  return json({
    {"type", "REMOVE_LOCK"},
    {"lock", key},
  }).dump();
}
