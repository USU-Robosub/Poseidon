#include "Hub.hpp"

void Hub::send(std::string connection, std::string data){
  if(connections.find(connection) != connections.end()){
    connections[connection]->send(data);
  }else{
    throw "The connection " + connection + " could not be found";
  }
}

void Hub::use(std::string nodeName, Node* node){
  if (nodes.find(nodeName) == nodes.end()){
    node->setName(nodeName);
    nodes[nodeName]=node;
    nodeNames.push_back(nodeName);
  }else{
    throw "The node name " + nodeName + " is already in use";
  }
}

void Hub::connect(std::string connectionName, Connection* connection){
  if (connections.find(connectionName) == connections.end()){
    connections[connectionName]=connection;
    connectionNames.push_back(connectionName);
  }else{
    throw "The connection name " + connectionName + " is already in use";
  }
}

void Hub::listen(){
  shouldListen = true;
  while(shouldListen){
    // TODO: stuff
  }
}

std::string Hub::getName(){
  return hubName;
}

std::vector<std::string> Hub::getNodeNames(){
  return nodeNames;
}

std::vector<std::string> Hub::getConnectionNames(){
  return connectionNames;
}

void Hub::exit(){
  shouldListen = false;
}
