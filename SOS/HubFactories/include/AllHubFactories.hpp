#ifndef ALL_HUB_FACTORIES_H
#define ALL_HUB_FACTORIES_H

#include <queue>
#include "ClusterConfig.hpp"
#include "HubFactory.hpp"
#include "Hub.hpp"

std::queue<HubFactory_ptr> getAllHubFactories(){
  std::queue<HubFactory_ptr> hubFactories;
  // example: hubFactories.push(HMC5883L_Compass_SensorFactory());
  // sensor hubs
  // actuator hubs
  return hubFactories;
}

std::vector<Hub_ptr> createAllHubs(std::queue<HubFactory_ptr> hubFactoryQueue, ClusterConfig clusterConfig){
  std::vector<Hub_ptr> hubs;
  while(!hubFactoryQueue.empty()){
    std::vector<Hub_ptr> newHubs = hubFactoryQueue.front()->createHubs(clusterConfig);
    hubs.insert(hubs.end(), newHubs.begin(), newHubs.end());
    hubFactoryQueue.pop();
  }
  return hubs;
}

#endif
