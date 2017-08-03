#ifndef ALL_PIPE_FACTORIES_H
#define ALL_PIPE_FACTORIES_H

#include <queue>
#include "PipeFactory.hpp"
#include "PipeGroup.hpp"
#include "ClusterConfig.hpp"

std::queue<PipeFactory_ptr> getAllPipeFactories();

PipeGroup createAllPipes(std::queue<PipeFactory_ptr>, ClusterConfig);

#endif
