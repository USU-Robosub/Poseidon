#ifndef NODE_FINDER_H
#define NODE_FINDER_H

#include <map>
#include <vector>
#include <string>
#include "Node.hpp"

class Router : public Node{
public:
  void update(IHub* hub);
  void process(IHub* hub, std::string connection, json message);
private:
  std::string generate_I_EXSIST(std::string hub, std::vector<std::string> nodes);
  bool firstUpdate = true;
  std::map<std::string, std::string> allHubs;
  std::map<std::string, std::string> allNodes;
};

#endif
