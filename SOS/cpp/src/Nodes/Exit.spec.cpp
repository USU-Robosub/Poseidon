#include "gtest/gtest.h"
#include "Exit.hpp"
#include "Hub.mock.hpp"

using ::testing::StrictMock;
using ::testing::Return;

TEST(Exit, makesHubExitOnExitMessage){
  MockHub mockHub;
  std::string connectionName = "connection";
  Exit exitNode;
  exitNode.setName("exitNode");

  Message exitMessage = Message().to("exitNode").ofType("exit").from("test").withNoData();
  EXPECT_CALL(mockHub, exit());
  ASSERT_NO_THROW(
    exitNode.process(&mockHub, &connectionName, &exitMessage)
  );
}

TEST(Exit, ignoresExitMessageForAnotherHub){
  DummyHub dummyHub;
  std::string connectionName = "connection";
  Exit exitNode;
  exitNode.setName("exitNode");

  Message exitMessage = Message().to("anotherExitNode").ofType("exit").from("test").withNoData();
  ASSERT_NO_THROW(
    exitNode.process(&dummyHub, &connectionName, &exitMessage)
  );
}

TEST(Exit, ignoresNonExitMessages){
  DummyHub dummyHub;
  std::string connectionName = "connection";
  Exit exitNode;
  exitNode.setName("exitNode");

  Message nonExitMessage = Message().to("exitNode").ofType("type").from("test").withNoData();
  ASSERT_NO_THROW(
    exitNode.process(&dummyHub, &connectionName, &nonExitMessage)
  );
}
