#ifndef PIPE_FACTORY_H
#define PIPE_FACTORY_H

#include "PipeGroup.hpp"

class PipeFactory{
public:
  virtual PipeGroup createPipes(ClusterConfig) = 0;
};

typedef std::shared_ptr<PipeFactory> PipeFactory_ptr;

#endif
