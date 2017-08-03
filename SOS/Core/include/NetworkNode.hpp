#ifndef NETWORK_NODE_H
#define NETWORK_NODE_H

#include <vector>
#include "Pipe.hpp"
#include "Hub.hpp"
#include "ClusterConfig.hpp"

class NetworkNode{
public:
  NetworkNode(ClusterConfig clusterConfig);
  void listenTo(std::vector<Pipe_ptr>);
  void relayTo(std::vector<Pipe_ptr>);
  void processWith(std::vector<Hub_ptr>);
  void listen();
};

#endif
