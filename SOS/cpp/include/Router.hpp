#ifndef NODE_FINDER_H
#define NODE_FINDER_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Node.hpp"

class Router : public Node{
public:
  Router() {};
  Router(std::map<std::string, std::string> allHubs, std::map<std::string, std::string> allNodes) : allHubs(allHubs), allNodes(allNodes) {};
  void update(IHub* hub);
  void process(IHub* hub, std::string* connection, Message* message);
private:
  void iExist(IHub* hub, std::string* connection, Message* message);
  void getAddresses(IHub* hub, std::string* connection, Message* message);
  void forward(IHub* hub, std::string* connection, Message* message);
  bool firstUpdate = true;
  std::map<std::string, std::string> allHubs;
  std::map<std::string, std::string> allNodes;
};

#endif
