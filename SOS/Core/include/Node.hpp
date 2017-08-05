#ifndef NODE_H
#define NODE_H

#include "json.hpp"
#include "IHub.hpp"

using json = nlohmann::json;

class Node{
public:
  virtual void update(IHub* hub) = 0;
  virtual void process(IHub* hub, json message) = 0;
};

#endif
