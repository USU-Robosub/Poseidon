#ifndef LOOPBACK_H
#define LOOPBACK_H

#include "Connection.hpp"

class Loopback : public Connection{
public:
  void send(std::string message);
  std::queue<std::string> read();
private:
  std::queue<std::string> messages;
};

#endif
