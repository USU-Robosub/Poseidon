#ifndef PID_TO_THRUSTER_H
#define PID_TO_THRUSTER_H

#include "Node.hpp"

class PIDtoThruster : public Node{
public:
  PIDtoThruster(std::string thrusterName) : thrusterName(thrusterName) {}
  void update(IHub* hub);
  void process(IHub* hub, std::string* connectionName, Message* message);
private:
  std::string thrusterName;
};

#endif
