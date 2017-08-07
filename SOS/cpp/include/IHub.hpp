#ifndef I_HUB_H
#define I_HUB_H

#include <string>
#include <vector>
#include <map>
#include "json.hpp"

using json = nlohmann::json;

class IHub{
public:
  virtual void send(std::string connection, std::string data) = 0;
  virtual std::string getName() = 0;
  virtual std::vector<std::string> getNodeNames() = 0;
  virtual std::vector<std::string> getConnectionNames() = 0;
  virtual void exit() = 0;
};

#endif
