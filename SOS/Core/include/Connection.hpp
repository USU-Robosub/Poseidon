#ifndef CONNECTION_H
#define CONNECTION_H

#include <queue>
#include <string>

class Connection{
public:
  virtual void send(std::string message) = 0;
  virtual std::queue<std::string> read() = 0;
};

#endif
