#ifndef NODE_H
#define NODE_H

#include "json.hpp"
#include "Hub.hpp"

class Node{
public:
  virtual void update(Hub* hub) = 0;
  virtual void process(Hub* hub, json request) = 0;
};

#endif
