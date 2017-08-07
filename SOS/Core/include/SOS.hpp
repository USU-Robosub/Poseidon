#ifndef SOS_H
#define SOS_H

#include "Hub.hpp"
#include "PseudoGUID.hpp"

#include "Router.hpp"
#include "Loopback.hpp"
#include "Locker.hpp"

class SOS{
public:
  SOS(bool isMaster) : locker(generateUUID), isMaster(isMaster) {}
  void mountTo(Hub* hub);
private:
  bool isMaster;
  Router router;
  Loopback loopback;
  Locker locker;
};

#endif
