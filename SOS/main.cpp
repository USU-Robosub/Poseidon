//#include "Assembler.hpp"
#include "NetworkNode.hpp"
#include "ClusterConfig.hpp"
#include "ClusterConfigFactory.hpp"
#include "PipeGroup.hpp"
#include "AllHubFactories.hpp"
#include "AllPipeFactories.hpp"
#include "HubFactory.hpp"
#include "PipeFactory.hpp"

int main(int argCount, char** arguments) {
  ClusterConfig clusterConfig = ClusterConfigFactory().generateConfig(argCount, arguments);
  NetworkNode networkNode(clusterConfig);

  // InboundPipe -> allows receiving data from another node
  // OutboundPipe -> allows sending data to another node
  std::queue<PipeFactory_ptr> pipeFactories = getAllPipeFactories();
  PipeGroup pipes = createAllPipes(pipeFactories, clusterConfig);
  networkNode.listenTo(pipes.inboundPipes);
  networkNode.relayTo(pipes.outboundPipes);

  // Hub -> takes in data from pipes (command), and outputs data to other pipes
  std::queue<HubFactory_ptr> hubFactories = getAllHubFactories();
  std::vector<Hub_ptr> hubs = createAllHubs(hubFactories, clusterConfig);
  networkNode.processWith(hubs);

  // starts loop that will read from inbound pipes
  networkNode.listen();
  return 0;
}
