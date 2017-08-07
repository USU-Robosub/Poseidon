#include "SOS.hpp"

void SOS::mountTo(Hub* hub){
  // mount system nodes
  hub->use("ROUTER", &router);
  if(isMaster){ hub->use("LOCKER", &locker); }
  // mount system connections
  hub->connect("LOCAL", &loopback);
}
