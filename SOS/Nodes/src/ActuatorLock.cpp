#include "ActuatorLock.hpp"

void ActuatorLock::update(IHub* hub){
  // do nothing
}

void ActuatorLock::process(IHub* hub, json message){
  auto from = message["from"];
  auto to = message["to"];
  auto request = message["request"];
  if(request["type"].get<std::string>() == "LOCK"){
    std::string key = generateUUID();
    std::string actuator = request["hub"].get<std::string>() + "|" + request["node"].get<std::string>();
    if(locks.find(actuator) == locks.end()){
      locks.insert(std::pair<std::string,std::string>(actuator, key));
      hub->send(request["hub"], request["node"], json({
        {"type", "APPLY_LOCK"},
        {"lock", key},
      }).dump());
      hub->send(from["hub"], from["node"], json({
        {"type", "GRANT_LOCK"},
        {"hub", request["hub"]},
        {"node", request["node"]},
        {"lock", key},
      }).dump());
    }else{
      hub->send(from["hub"], from["node"], json({
        {"type", "REJECT_LOCK"},
        {"hub", request["hub"]},
        {"node", request["node"]},
      }).dump());
    }
  }else if(request["type"] == "UNLOCK"){
    std::string key = request["lock"];
    std::string actuator = request["hub"].get<std::string>() + "|" + request["node"].get<std::string>();
    if(locks.find(actuator) != locks.end() && locks[actuator] == key){
      locks.erase(actuator);
      hub->send(request["hub"], request["node"], json({
        {"type", "REMOVE_LOCK"},
        {"lock", key},
      }).dump());
    }
  }else{
    hub->error("Lock command invalid");
  }
}
