#ifndef HUB_H
#define HUB_H

#include <string>
#include "Node.hpp"
#include "Connection.hpp"

class Hub{
public:
  Hub(std::string name);
  Hub(std::string name, std::string master);
  send(std::string hub, std::string node, std::string data);
  send(std::string node, std::string data); // <- use if hub knows how to get to the node
  address(std::string hubName, std::string nodeName);
  use(std::string nodeName, Node* node);
  connect(std::string hubName, Connection* connection);
  listen(); // returns when a SOS exit command is sent
  softClose(); // does not delete connections and nodes
  close(); // deletes connections and nodes
};

#endif
