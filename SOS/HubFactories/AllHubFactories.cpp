#include "HubFactory.h"

std::queue<HubFactory> getAllHubFactories(){
  std::queue<HubFactory> hubFactories;
  // example: hubFactories.push(HMC5883L_Compass_SensorFactory());
  // sensor hubs
  // actuator hubs
  return hubFactories;
}

std::vector<Hub> createAllHubs(std::queue<HubFactory> hubFactoryQueue, ClusterConfig clusterConfig){
  std::vector<Hub> hubs;
  while(!hubFactoryQueue.empty()){
    std::vector<Hub> newHubs = hubFactoryQueue.front().createHubs(clusterConfig);
    hubs.insert(hubs.end(), newHubs.begin(), newHubs.end());
    hubFactoryQueue.pop();
  }
  return hubs;
}
