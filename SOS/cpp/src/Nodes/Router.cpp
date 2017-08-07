#include "Router.hpp"

void Router::update(IHub* hub){
  if(firstUpdate){
    firstUpdate = false;
    std::vector<std::string> connections(hub->getConnectionNames());
    for(unsigned int i = 0; i < connections.size(); i++){
      hub->send(connections[i], generate_I_EXSIST(hub->getName(), hub->getNodeNames()));
    }
  }
}

void Router::process(IHub* hub, std::string connection, json message){
  std::vector<std::string> hubNodes = hub->getNodeNames();
  if(std::find(hubNodes.begin(), hubNodes.end(), message["target"]) != hubNodes.end()){ // target exists on this hub
    auto data = message["data"];
    if(message["target"] == nodeName){
      if(message["type"] == "I_EXSIST"){
        if(allHubs.find(data["hub"]) == allHubs.end()){
          allHubs[data["hub"]] = connection;
          allNodes[data["nodes"]] = data["hub"];
          std::vector<std::string> connections(hub->getConnectionNames());
          for(unsigned int i = 0; i < connections.size(); i++){
            if(connections[i] != connection){
              hub->send(connections[i], message.dump());
            }
          }
          hub->send(connection, generate_I_EXSIST(hub->getName(), hub->getNodeNames()));
        }
      }
    }
  }else{
    hub->send(allHubs[allNodes[message["target"]]], message.dump());
  }
}

std::string Router::generate_I_EXSIST(std::string hub, std::vector<std::string> nodes){
  return json({
    {"type", "I_EXSIST"},
    {"target", nodeName},
    {"from", nodeName},
    {"data", {
      {"hub", hub},
      {"nodes", nodes}
    }},
  }).dump();
}
