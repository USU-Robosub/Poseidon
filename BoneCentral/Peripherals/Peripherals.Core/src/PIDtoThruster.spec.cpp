#include "gtest/gtest.h"
#include "PIDtoThruster.h"
#include "Hub.mock.hpp"

using ::testing::StrictMock;

TEST(PIDtoThruster, acceptsSet){
  MockHub mockHub;
  std::string connectionName = "connection";
  PIDtoThruster pidToThruster("actuatorName");
  pidToThruster.setName("PIDtoThruster");

  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "SET_POWER", "PIDtoThruster", json({
    {"power", 10}
  }))));
  Message setMessage("PIDtoThruster", "SET", "someone", json({
    {"correctionValue", 10}
  }));
  ASSERT_NO_THROW(
    pidToThruster.process(&mockHub, &connectionName, &setMessage)
  );
}

TEST(PIDtoThruster, ignoreSetForAnotherNode){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDtoThruster pidToThruster("actuatorName");
  pidToThruster.setName("PIDtoThruster");

  Message setMessage("anotherNode", "SET", "someone", json({
    {"correctionValue", 10}
  }));
  ASSERT_NO_THROW(
    pidToThruster.process(&mockHub, &connectionName, &setMessage)
  );
}

TEST(PIDtoThruster, ignoreMalformedSet){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDtoThruster pidToThruster("actuatorName");
  pidToThruster.setName("PIDtoThruster");

  Message setMessage("PIDtoThruster", "SET", "someone", json({
    {"data", "something"}
  }));
  ASSERT_NO_THROW(
    pidToThruster.process(&mockHub, &connectionName, &setMessage)
  );
}

TEST(PIDtoThruster, acceptsStop){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDtoThruster pidToThruster("actuatorName");
  pidToThruster.setName("PIDtoThruster");

  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "SET_POWER", "PIDtoThruster", json({
    {"power", 0}
  }))));
  Message stopMessage("PIDtoThruster", "STOP", "someone");
  ASSERT_NO_THROW(
    pidToThruster.process(&mockHub, &connectionName, &stopMessage)
  );
}
