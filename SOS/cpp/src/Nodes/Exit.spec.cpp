#include "gtest/gtest.h"
#include "Exit.hpp"
#include "Hub.mock.hpp"

using ::testing::StrictMock;
using ::testing::Return;

TEST(Exit, noExit){
  StrictMock<MockHub> hub;
  Exit exitNode;
  exitNode.setName("MockHub_EXIT");
  exitNode.process(&hub, "test", json({
    {"target", "otherHub_exit"},
    {"type", "EXIT"}
  }));
}

TEST(Exit, exitOn_EXIT){
  MockHub hub;
  Exit exitNode;
  EXPECT_CALL(hub, exit());
  exitNode.setName("MockHub_EXIT");
  exitNode.process(&hub, "test", json({
    {"target", "MockHub_EXIT"},
    {"type", "EXIT"}
  }));
}
