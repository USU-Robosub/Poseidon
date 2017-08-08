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
      if(message["type"] == "I_EXIST"){
        if(allHubs.find(data["hub"]) == allHubs.end()){
          allHubs[data["hub"]] = connection;
          std::vector<std::string> nodes = data["nodes"];
          for(unsigned int i = 0; i < nodes.size(); i++){
            allNodes[nodes[i]] = data["hub"];
          }
          std::vector<std::string> connections(hub->getConnectionNames());
          for(unsigned int i = 0; i < connections.size(); i++){
            if(connections[i] != connection){
              hub->send(connections[i], message.dump());
            }
          }
          hub->send(connection, generate_I_EXSIST(hub->getName(), hubNodes));
        }
      }else if(message["type"] == "GET_ADDRESSES"){
        hub->send(connection, generate_GET_ADRESSES(message["from"]));
      }
    }
  }else{
    hub->send(allHubs[allNodes[message["target"]]], message.dump());
  }
}

std::string Router::generate_I_EXSIST(std::string hub, std::vector<std::string> nodes){
  return json({
    {"type", "I_EXIST"},
    {"target", nodeName},
    {"from", nodeName},
    {"data", {
      {"hub", hub},
      {"nodes", nodes}
    }},
  }).dump();
}

std::string Router::generate_GET_ADRESSES(std::string target){
  return json({
    {"type", "GOT_ADDRESSES"},
    {"target", target},
    {"from", nodeName},
    {"data", {
      {"hubs", allHubs},
      {"nodes", allNodes}
    }},
  }).dump();
}
