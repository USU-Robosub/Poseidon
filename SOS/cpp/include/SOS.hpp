#ifndef SOS_H
#define SOS_H

#include "Hub.hpp"
#include "PseudoGUID.hpp"
#include "Node.hpp"

#include "Router.hpp"
#include "Loopback.hpp"
#include "Locker.hpp"
#include "Exit.hpp"

class SOS{
public:
  SOS() : locker(generateUUID) {}
  void becomeMaster(Node* node);
  void runOn(Hub* hub);
private:
  bool isMaster = false;
  Router router;
  Loopback loopback;
  Locker locker;
  Exit exitNode;
  Node* logger;
};

#endif
