#include "Router.hpp"

void Router::update(IHub* hub){
  if(firstUpdate){
    firstUpdate = false;
    std::vector<std::string> connections(hub->getConnectionNames());
    for(unsigned int i = 0; i < connections.size(); i++){
      hub->send(connections[i], Message(nodeName, "I_EXIST", nodeName, json({
        {"hub", hub->getName()},
        {"nodes", hub->getNodeNames()}
      })));
    }
  }
}

void Router::process(IHub* hub, std::string* connection, Message* message){
  std::vector<std::string> hubNodes = hub->getNodeNames();
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("I_EXIST"))            iExist(hub, connection, message);
    else if(message->matchesType("GET_ADDRESSES")) getAddresses(hub, connection, message);
  }else if(std::find(hubNodes.begin(), hubNodes.end(), message->getTarget()) == hubNodes.end())
    forward(hub, connection, message);
}

void Router::iExist(IHub* hub, std::string* connection, Message* message){
  std::string hubName = message->getData()["hub"];
  if(allHubs.find(hubName) == allHubs.end()){
    allHubs[hubName] = *connection;
    std::vector<std::string> nodes = message->getData()["nodes"];
    for(unsigned int i = 0; i < nodes.size(); i++){
      allNodes[nodes[i]] = hubName;
    }
    std::vector<std::string> connections(hub->getConnectionNames());
    for(unsigned int i = 0; i < connections.size(); i++){
      if(connections[i] != *connection) hub->send(connections[i], *message);
    }
    hub->send(*connection, Message(nodeName, "I_EXIST", nodeName, json({
      {"hub", hub->getName()},
      {"nodes", hub->getNodeNames()}
    })));
  }
}

void Router::getAddresses(IHub* hub, std::string* connection, Message* message){
  hub->send(*connection, Message(message->getSender(), "GOT_ADDRESSES", nodeName, json({
    {"hubs", allHubs},
    {"nodes", allNodes}
  })));
}

void Router::forward(IHub* hub, std::string* connection, Message* message){
  if(allNodes.find(message->getTarget()) != allNodes.end() &&
      allHubs.find(allNodes[message->getTarget()]) != allHubs.end()){
    hub->send(allHubs[allNodes[message->getTarget()]], *message);
  }else{
    hub->send(*connection, Message(message->getSender(), "ROUTE_NOT_FOUND", nodeName, json({
      {"target", message->getTarget()}
    })));
    hub->logError("Route not found to \"" + message->getTarget() + "\" from \"" + hub->getName() + "\"");
  }
}
