#include "PipeFactory.h"
#include "PipeGroup.h"

std::queue<PipeFactory> getAllPipeFactories(){
  std::queue<PipeFactory> pipeFactories;
  // example: pipeFactories.push(Arduino_USB_PipeFactory());
  // device pipes
  // hardware pipes
  return pipeFactories;
}

PipeGroup createAllPipes(std::queue<PipeFactory> pipeFactoryQueue, ClusterConfig clusterConfig){
  PipeGroup hubs;
  while(!pipeFactoryQueue.empty()){
    PipeGroup newPipes = pipeFactoryQueue.front().createPipes(clusterConfig);
    hubs.inboundPipes.insert(hubs.inboundPipes.end(), newPipes.inboundPipes.begin(), newPipes.inboundPipes.end());
    hubs.outboundPipes.insert(hubs.outboundPipes.end(), newPipes.outboundPipes.begin(), newPipes.outboundPipes.end());
    pipeFactoryQueue.pop();
  }
  return hubs;
}
