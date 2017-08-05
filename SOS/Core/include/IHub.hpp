#ifndef I_HUB_H
#define I_HUB_H

class IHub{
public:
  virtual void send(std::string hub, std::string node, std::string data) = 0;
  virtual void send(std::string node, std::string data) = 0;
  virtual void error(std::string message) = 0;
  virtual void lock(std::string hub, std::string node) = 0;
};

#endif
