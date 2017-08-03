#ifndef MOCK_PIPE_FACTORY_H
#define MOCK_PIPE_FACTORY_H

#include "gmock/gmock.h"
#include "PipeFactory.hpp"

class MockPipeFactory : public PipeFactory {
public:
  MOCK_METHOD1(createPipes, PipeGroup(ClusterConfig clusterConfig));
};

#endif
