#include "gtest/gtest.h"
#include "Exit.hpp"
#include "Hub.mock.hpp"

using ::testing::StrictMock;
using ::testing::Return;

TEST(Exit, noExit){
  std::string connectionName = "test";
  StrictMock<MockHub> hub;
  Message message("otherHub_exit", "EXIT", "", json({}));
  Exit exitNode;
  exitNode.setName("MockHub_EXIT");
  exitNode.process(&hub, &connectionName, &message);
}

TEST(Exit, exitOn_EXIT){
  std::string connectionName = "test";
  MockHub hub;
  Message message("MockHub_EXIT", "EXIT", "", json({}));
  Exit exitNode;
  EXPECT_CALL(hub, exit());
  exitNode.setName("MockHub_EXIT");
  exitNode.process(&hub, &connectionName, &message);
}
