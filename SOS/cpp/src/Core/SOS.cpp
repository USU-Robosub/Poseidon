#include "SOS.hpp"

void SOS::runOn(Hub* hub){
  // mount system nodes
  hub->use("ROUTER", &router);
  hub->use(hub->getName() + "_EXIT", &exitNode);
  if(isMaster){
    hub->use("LOCKER", &locker);
    hub->use("LOGGER", logger);
  }
  // mount system connections
  hub->connect("LOCAL", &loopback);
}

void SOS::becomeMaster(Node* node){
  isMaster = true;
  logger = node;
}
