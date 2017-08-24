#include "gtest/gtest.h"
#include "Thruster.h"
#include "Hub.mock.hpp"

using ::testing::_;

TEST(Thruster, process_setPower){
  MockHub hub;
  Message setPower("");
  std::string connectionName = "connection";
  Thruster thruster("arduino", 0);
  thruster.setName("thruster");

  // correct data
  EXPECT_CALL(hub, send("LOCAL", Message("arduino", "WRITE_BYTE", "thruster", json({
    {"byte", 0}
  }))));
  EXPECT_CALL(hub, send("LOCAL", Message("arduino", "WRITE_SHORT", "thruster", json({
    {"short", 6500}
  }))));
  setPower = Message("thruster", "SET_POWER", "test", json({
    {"power", 10}
  }));
  thruster.process(&hub, &connectionName, &setPower);

  // incorrect data type
  setPower = Message("thruster", "SET_POWER", "test", json({
    {"power", "10"}
  }));
  thruster.process(&hub, &connectionName, &setPower);

  // incorrect data
  setPower = Message("thruster", "SET_POWER", "test", json({
    {"other", "test"}
  }));
  thruster.process(&hub, &connectionName, &setPower);
}
