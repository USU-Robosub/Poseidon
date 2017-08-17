#ifndef I_HUB_H
#define I_HUB_H

#include <string>
#include <vector>
#include <map>
#include "Message.hpp"

class IHub{
public:
  virtual void send(std::string connectionName, Message message) = 0;
  virtual std::string getName() = 0;
  virtual std::vector<std::string> getNodeNames() = 0;
  virtual std::vector<std::string> getConnectionNames() = 0;
  virtual void exit() = 0;
};

#endif
