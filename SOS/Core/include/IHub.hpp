#ifndef I_HUB_H
#define I_HUB_H

#include <string>
#include <vector>
#include <map>
#include "json.hpp"

using json = nlohmann::json;

class IHub{
public:
  //virtual void send(std::string connection, std::string fromNode, std::string toHub, std::string toNode, std::string data) = 0;
  virtual void send(std::string connection, std::string data) = 0;
  virtual std::vector<std::string> getName() = 0;
  virtual std::vector<std::string> getNodeNames() = 0;
  virtual std::vector<std::string> getConnectionNames() = 0;
  //virtual void send(std::string fromNode, std::string toHub, std::string toNode, std::string data) = 0;
  //virtual void send(std::string fromNode, std::string toNode, std::string data) = 0;

  //virtual void error(std::string message) = 0;
  //virtual void lock(std::string hub, std::string node) = 0;
};

#endif
