#include "SOS.hpp"

void SOS::runOn(Hub* hub){
  // mount system nodes
  hub->use("ROUTER", &router);
  if(isMaster){ hub->use("LOCKER", &locker); }
  // mount system connections
  hub->connect("LOCAL", &loopback);
}
