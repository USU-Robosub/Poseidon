//#include "Assembler.h"
#include "NetworkNode.h"
#include "ClusterConfig.h"
#include "ClusterConfigFactory.h"
#include "PipeGroup.h"
#include "AllHubFactories.cpp"
#include "AllPipeFactories.cpp"

int main(int argCount, char** arguments) {
  ClusterConfig clusterConfig = ClusterConfigFactory.generateConfig(int argCount, char** argument);
  NetworkNode networkNode(clusterConfig);

  // InboundPipe -> allows receiving data from another node
  // OutboundPipe -> allows sending data to another node
  std::queue<PipeFactory> pipeFactories = getAllPipeFactories();
  PipeGroup pipes = createAllPipes(pipeFactories, clusterConfig);
  networkNode.listenTo(pipes.inboundPipes);
  networkNode.relayTo(pipes.outboundPipes);

  // Hub -> takes in data from pipes (command), and outputs data to other pipes
  std::queue<HubFactory> hubFactories = getAllHubFactories()
  std::vector<Hub> hubs = createAllHubs(hubFactories, clusterConfig);
  networkNode.processWith(hubs);

  // starts loop that will read from inbound pipes
  networkNode.listen();
  return 0;
}
