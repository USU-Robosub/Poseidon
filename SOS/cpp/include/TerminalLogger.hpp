#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include "Node.hpp"

class TerminalLogger : public Node{
  void update(IHub* hub);
  void process(IHub* hub, std::string* connection, Message* message);
};

#endif
