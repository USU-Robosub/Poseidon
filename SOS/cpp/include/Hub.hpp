#ifndef HUB_H
#define HUB_H

#include <string>
#include <map>
#include "IHub.hpp"
#include "Node.hpp"
#include "Connection.hpp"

class Hub : public IHub{
public:
  Hub(std::string name) : hubName(name) {}
  void send(std::string connection, std::string data);
  void use(std::string nodeName, Node* node);
  void connect(std::string hubName, Connection* connection);
  void listen();
  std::string getName();
  std::vector<std::string> getNodeNames();
  std::vector<std::string> getConnectionNames();
  void exit();
private:
  bool shouldListen = false;
  std::string hubName;
  std::map<std::string, Connection*> connections;
  std::vector<std::string> connectionNames;
  std::map<std::string, Node*> nodes;
  std::vector<std::string> nodeNames;
};

#endif
