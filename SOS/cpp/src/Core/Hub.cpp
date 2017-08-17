#include "Hub.hpp"

void Hub::send(std::string connectionName, Message message){
  if(connections.find(connectionName) != connections.end()){
    connections[connectionName]->send(message.toJsonString());
  }else{
    throw "The connection " + connectionName + " could not be found";
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
  std::chrono::milliseconds interval(10);
  while(shouldListen){
    std::this_thread::sleep_for(interval);
    updateNodes();
    passMessagesToNodes(readAllMessages());
  }
}

void Hub::updateNodes(){
  for(unsigned int i = 0; i < nodeNames.size(); i++){
    nodes[nodeNames[i]]->update(this);
  }
}

std::vector<std::queue<std::string>> Hub::readAllMessages(){
  std::vector<std::queue<std::string>> messages;
  for(unsigned int i = 0; i < connectionNames.size(); i++){
    messages.push_back(connections[connectionNames[i]]->read());
  }
  return messages;
}

void Hub::passMessagesToNodes(std::vector<std::queue<std::string>> messages){
  for(unsigned int i = 0; i < messages.size(); i++){
    while(!messages[i].empty()){
      Message message(messages[i].front());
      if(!message.isMalformed()){
        for(unsigned int j = 0; j < nodeNames.size(); j++){
          nodes[nodeNames[j]]->process(this, &connectionNames[i], &message);
        }
      }
      messages[i].pop();
    }
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
