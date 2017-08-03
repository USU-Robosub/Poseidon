#ifndef ALL_HUB_FACTORIES_H
#define ALL_HUB_FACTORIES_H

#include <queue>
#include "ClusterConfig.hpp"
#include "HubFactory.hpp"
#include "Hub.hpp"

std::queue<HubFactory_ptr> getAllHubFactories();

std::vector<Hub_ptr> createAllHubs(std::queue<HubFactory_ptr> hubFactoryQueue, ClusterConfig clusterConfig);

#endif
