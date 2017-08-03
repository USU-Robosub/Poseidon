#ifndef CLUSTER_CONFIG_FACTORY_H
#define CLUSTER_CONFIG_FACTORY_H

#include "ClusterConfig.hpp"

class ClusterConfigFactory{
public:
  ClusterConfig generateConfig(int argCount, char** arguments);
};

#endif
