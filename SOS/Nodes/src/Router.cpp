#include "Router.hpp"

void Router::update(IHub* hub){
  if(firstUpdate){
    firstUpdate = false;
    std::vector<std::string> connections(hub->getConnectionNames());
    for(unsigned int i = 0; i < connections.size(); i++){
      hub.send(connections[i], generate_I_EXSIST(hub.getName(), hub->getNodeNames()));
    }
  }
}

void Router::process(IHub* hub, std::string connection, json message){
  std::vector<std::string> hubNodes = hub->getNodeNames();
  if(hubNodes.find(message["target"]) != hubNodes.end()){ // target exists on this hub
    auto data = message["data"];
    if(message["target"] == "SOS_ANY"){
      if(message["type"] == "SOS_I_EXSIST"){
        if(allHubs.find(data["hub"]) == allHubs.end()){
          allHubs[data["hub"]] = connection;
          allNodes[data["nodes"]] = data["hub"];
          std::vector<std::string> connections(hub->getConnectionNames());
          for(unsigned int i = 0; i < connections.size(); i++){
            if(connections[i] != connection){
              hub->send(connections[i], message.dump());
            }
          }
        }
      }
    }
  }else{
    hub->send(allHubs[allNodes[message["target"]]], message.dump());
  }
}

std::string Router::generate_I_EXSIST(std::string hub, std::vector<std::string> nodes){
  return json({
    {"type": "SOS_I_EXSIST"},
    {"target", "SOS_ANY"},
    {"from", nodeName},
    {"data", {
      {"hub", hub},
      {"nodes", nodes}
    }},
  }).dump();
}
