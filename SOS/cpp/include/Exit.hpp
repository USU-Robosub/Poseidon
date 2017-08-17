#ifndef EXIT_H
#define EXIT_H

#include "Node.hpp"

class Exit : public Node{
public:
  void update(IHub* hub);
  void process(IHub* hub, std::string* connection, Message* message);
};

#endif
