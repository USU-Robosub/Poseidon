#ifndef NODE_H
#define NODE_H

#include "IHub.hpp"

class Node{
public:
  virtual void setName(std::string name) = 0;
  virtual void update(IHub* hub) = 0;
  virtual void process(IHub* hub, json message) = 0;
};

#endif
