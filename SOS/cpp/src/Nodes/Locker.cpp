#include "Locker.hpp"
#include <iostream>

void Locker::update(IHub* hub){
  // do nothing
}

void Locker::process(IHub* hub, std::string connection, json message){
  if(message["target"] == nodeName){
    if(message["type"] == "LOCK"){
      auto data = message["data"];
      std::string nodeName = data["node"];
      if(locks.find(nodeName) == locks.end()){
        std::string key = generateUUID();
        locks[nodeName] = key;
        hub->send("LOCAL", generateAPPLY_LOCK(data["node"], key));
        hub->send(connection, generateGRANT_LOCK(message["from"], data["node"], key));
      }else{
        hub->send(connection, generateREJECT_LOCK(message["from"], data["node"]));
      }
    }else if(message["type"] == "UNLOCK"){
      auto data = message["data"];
      std::string nodeName = data["node"];
      if(locks.find(nodeName) != locks.end() && locks[nodeName] == data["key"]){
        hub->send("LOCAL", generateREMOVE_LOCK(data["node"], locks[nodeName]));
        locks.erase(nodeName);
      }
    }else if(message["type"] == "FORCE_UNLOCK_ALL"){
      for (auto& lock : locks){
        std::string const& node = lock.first;
        std::string const& key = lock.second;
        hub->send("LOCAL", generateREMOVE_LOCK(node, key));
      }
      locks.clear();
    }
  }
}

std::string Locker::generateAPPLY_LOCK(std::string target, std::string key) {
  return json({
    {"type", "APPLY_LOCK"},
    {"target", target},
    {"from", nodeName},
    {"data", {
      {"key", key}
    }}
  }).dump();
}

std::string Locker::generateGRANT_LOCK(std::string target, std::string node, std::string key){
  return json({
    {"type", "GRANT_LOCK"},
    {"target", target},
    {"from", nodeName},
    {"data", {
      {"key", key},
      {"node", node}
    }}
  }).dump();
}

std::string Locker::generateREJECT_LOCK(std::string target, std::string node){
  return json({
    {"type", "REJECT_LOCK"},
    {"target", target},
    {"from", nodeName},
    {"data", {
      {"node", node}
    }}
  }).dump();
}


std::string Locker::generateREMOVE_LOCK(std::string target, std::string key){
  return json({
    {"type", "REMOVE_LOCK"},
    {"target", target},
    {"from", nodeName},
    {"data", {
      {"key", key}
    }}
  }).dump();
}
