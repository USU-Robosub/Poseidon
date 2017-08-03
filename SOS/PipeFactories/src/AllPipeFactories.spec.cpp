#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AllPipeFactories.hpp"
#include "Pipe.mock.hpp"
#include "PipeFactory.mock.hpp"
#include "ClusterConfig.mock.hpp"
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

TEST(AllPipeFactories, getAllPipeFactories) {
  std::queue<PipeFactory_ptr> pipeFactories = getAllPipeFactories();
  EXPECT_EQ(0, pipeFactories.size());
}

TEST(AllPipeFactories, createAllPipes){
  // create mock pipe group
  PipeGroup mockGroup;
  mockGroup.inboundPipes.push_back(Pipe_ptr(new MockPipe()));
  mockGroup.outboundPipes.push_back(Pipe_ptr(new MockPipe()));
  // create mock pipe
  MockPipeFactory* mock = new MockPipeFactory();
  MockClusterConfig mockConfig;
  EXPECT_CALL(*mock, createPipes(_))
    .Times(AtLeast(1))
    .WillOnce(Return(mockGroup));
  // test if createAllPipes will run createPipes on the mock
  std::queue<PipeFactory_ptr> pipeFactories;
  pipeFactories.push(PipeFactory_ptr(mock));
  PipeGroup pipes = createAllPipes(pipeFactories, mockConfig);
  EXPECT_EQ(1, pipes.inboundPipes.size());
  EXPECT_EQ(1, pipes.outboundPipes.size());
}
