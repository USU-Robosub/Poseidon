#ifndef HUB_H
#define HUB_H

#include <string>
#include <map>
#include "IHub.hpp"
#include "Node.hpp"
#include "Connection.hpp"

class Hub : public IHub{
public:
  Hub(std::string name) : name(name) {}
  //Hub(std::string name, std::string master);

  void send(std::string connection, std::string fromNode, std::string toHub, std::string toNode, std::string data);
  void send(std::string fromNode, std::string toHub, std::string toNode, std::string data);
  void send(std::string fromNode, std::string toNode, std::string data);

  //void address(std::string hubName, std::string nodeName);
  void use(std::string nodeName, Node* node);
  void connect(std::string hubName, Connection* connection);
  void listen(); // returns when a SOS exit command is sent
  //void error(std::string message);
  //void lock(std::string hub, std::string node);
private:
  std::map<std::string, std::string> addresses;
  std::string name;
  std::map<std::string, Connection*> connections;
  std::map<std::string, Node*> nodes;
};

#endif
