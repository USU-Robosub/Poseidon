#ifndef HUB_H
#define HUB_H

#include <string>
#include <map>
#include <thread>
#include "IHub.hpp"
#include "Node.hpp"
#include "Connection.hpp"

class Hub : public IHub{
public:
  Hub(std::string name) : hubName(name) {}
  virtual void send(std::string connection, std::string data);
  virtual void use(std::string nodeName, Node* node);
  virtual void connect(std::string hubName, Connection* connection);
  virtual void listen();
  virtual std::string getName();
  virtual std::vector<std::string> getNodeNames();
  virtual std::vector<std::string> getConnectionNames();
  virtual void exit();
private:
  bool shouldListen = false;
  std::string hubName;
  std::map<std::string, Connection*> connections;
  std::vector<std::string> connectionNames;
  std::map<std::string, Node*> nodes;
  std::vector<std::string> nodeNames;
};

#endif
