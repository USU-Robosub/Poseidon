#ifndef NODE_H
#define NODE_H

#include "IHub.hpp"

class Node{
public:
  void setName(std::string name) { nodeName = name; }
  virtual void update(IHub* hub) = 0;
  virtual void process(IHub* hub, std::string connection, json message) = 0;
private:
  std::string nodeName;
};

#endif
