#ifndef THRUSTER_H
#define THRUSTER_H

#include "Node.hpp"

class Thruster : public Node{
public:
  Thruster(std::string arduinoName, int arduinoIndex) : arduinoName(arduinoName), arduinoIndex(arduinoIndex) {}
  void update(IHub* hub);
  void process(IHub* hub, std::string connection, json message);
private:
  std::string generate_GOT(std::string target, json value);
  std::string arduinoName;
  int arduinoIndex;
};

#endif
