#ifndef PIPE_GROUP_H
#define PIPE_GROUP_H

#include <vector>
#include "Pipe.hpp"

struct PipeGroup{
  std::vector<Pipe_ptr> outboundPipes;
  std::vector<Pipe_ptr> inboundPipes;
};

#endif
