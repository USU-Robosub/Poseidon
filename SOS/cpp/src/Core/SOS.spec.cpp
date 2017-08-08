#include "gtest/gtest.h"
#include "SOS.hpp"
#include "Hub.mock.hpp"
#include "Node.mock.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::A;

TEST(SOS, runOn){
  MockHub hub;
  SOS sos;
  EXPECT_CALL(hub, getName());
  ON_CALL(hub, getName()).WillByDefault(Return("MockHub"));
  EXPECT_CALL(hub, use("ROUTER", _));
  EXPECT_CALL(hub, use("MockHub_EXIT", _));
  EXPECT_CALL(hub, connect("LOCAL", _));
  sos.runOn(&hub);
}

TEST(SOS, runOn_master){
  MockHub hub;
  MockNode node;
  SOS sos;
  EXPECT_CALL(hub, getName());
  ON_CALL(hub, getName()).WillByDefault(Return("MockHub"));
  EXPECT_CALL(hub, use("ROUTER", _));
  EXPECT_CALL(hub, use("MockHub_EXIT", _));
  EXPECT_CALL(hub, use("LOCKER", _));
  EXPECT_CALL(hub, use("LOGGER", _));
  EXPECT_CALL(hub, connect("LOCAL", _));
  sos.becomeMaster(&node);
  sos.runOn(&hub);
}
