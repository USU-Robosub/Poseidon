#include "Hub.hpp"

void Hub::send(std::string connection, std::string fromNode, std::string toHub, std::string toNode, std::string data){
  connections[connection]->send(json({
    {"from", {
      {"hub", name},
      {"node", fromNode}
    }},
    {"to", {
      {"hub", toHub},
      {"node", toNode}
    }},
    {"request", json::parse(data)}
  }).dump());
}

void Hub::send(std::string fromNode, std::string toHub, std::string toNode, std::string data){
  send(toHub, fromNode, toHub, toNode, data);
}

void Hub::send(std::string fromNode, std::string toNode, std::string data){
  send(fromNode, addresses[toNode], toNode, data);
}

void Hub::address(std::string hubName, std::string nodeName){
  if (addresses.find(nodeName) == addresses.end()){
    addresses[nodeName]=hubName;
  }else{
    throw "The node name " + nodeName + " already has an address";
  }
}

void Hub::use(std::string nodeName, Node* node){
  if (nodes.find(nodeName) == nodes.end()){
    node->setName(nodeName);
    nodes[nodeName]=node;
  }else{
    throw "The node name " + nodeName + " is already in use";
  }
}

void Hub::connect(std::string hubName, Connection* connection){
  if (connections.find(hubName) == connections.end()){
    connections[hubName]=connection;
  }else{
    throw "The hub " + hubName + " is already connected";
  }
}

void Hub::listen(){

}
