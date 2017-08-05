#ifndef HUB_H
#define HUB_H

#include <string>
#include "IHub.hpp"
#include "Node.hpp"
#include "Connection.hpp"

class Hub : public IHub{
public:
  Hub(std::string name);
  Hub(std::string name, std::string master);
  void send(std::string hub, std::string node, std::string data);
  void send(std::string node, std::string data); // <- use if hub knows how to get to the node
  void address(std::string hubName, std::string nodeName);
  void use(std::string nodeName, Node* node);
  void connect(std::string hubName, Connection* connection);
  void listen(); // returns when a SOS exit command is sent
  void softClose(); // does not delete connections and nodes
  void close(); // deletes connections and nodes
  void error(std::string message);
  void lock(std::string hub, std::string node);
private:
  std::string currentNode;
};

#endif
