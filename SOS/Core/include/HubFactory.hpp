#ifndef HUB_FACTORY_H
#define HUB_FACTORY_H

#include <vector>
#include "Hub.hpp"
#include "ClusterConfig.hpp"

class HubFactory{
public:
  virtual std::vector<Hub_ptr> createHubs(ClusterConfig) = 0;
};

typedef std::shared_ptr<HubFactory> HubFactory_ptr;

#endif
