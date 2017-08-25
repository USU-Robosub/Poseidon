#include "gtest/gtest.h"
#include "PIDnode.h"
#include "Hub.mock.hpp"

using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::_;

TEST(PIDnode, canCreatePIDnode){
  ASSERT_NO_THROW(
    PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
    ASSERT_FALSE(PID.isEnabled());
  );
}

TEST(PIDnode, acceptsEnable){
  NiceMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");

  Message enableMessage("PID", "ENABLE", "someone");
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &enableMessage);
    ASSERT_TRUE(PID.isEnabled());
  );
}

TEST(PIDnode, acceptsDisableAndDisablesUpdateAndSendsStopToActuator){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");
  PID.enable();

  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "STOP", "PID")));
  Message disableMessage("PID", "DISABLE", "someone");
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &disableMessage);
    ASSERT_FALSE(PID.isEnabled());
    PID.update(&mockHub);
  );
}

TEST(PIDnode, everyUpdateSendsCorrectionValueAndPollsFromSensor){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");
  PID.enable();

  EXPECT_CALL(mockHub, send("LOCAL", Message("sensorName", "GET", "PID")));
  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "SET", "PID", json({
    {"correctionValue", 0}
  }))));
  ASSERT_NO_THROW(
    PID.update(&mockHub);
  );
}

TEST(PIDnode, acceptsGOTfromSensor){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");

  Message gotMessage("PID", "GOT", "sensorName", json({
    {"value", 1}
  }));
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &gotMessage);
    ASSERT_EQ(PID.getLastSensorReading(), 1);
  );
}

TEST(PIDnode, acceptsSetTarget){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");

  Message setTargetMessage("PID", "SET_TARGET", "someone", json({
    {"target", 13}
  }));
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &setTargetMessage);
    ASSERT_EQ(PID.getTarget(), 13);
  );
}

TEST(PIDnode, acceptsSetConfig){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");

  Message setConfigMessage("PID", "SET_CONFIG", "someone", json({
    {"P", 10},
    {"I", 20},
    {"D", 30}
  }));
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &setConfigMessage);
    ASSERT_EQ(PID.getP(), 10);
    ASSERT_EQ(PID.getI(), 20);
    ASSERT_EQ(PID.getD(), 30);
  );
}

TEST(PIDnode, ignoreSetDeltaTime){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");

  Message setDeltaTimeMessage("PID", "SET_DELTA_TIME", "someone", json({
    {"deltaTime", 10},
  }));
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &setDeltaTimeMessage);
  );
}

TEST(PIDnode, onlyAcceptsGOTforPIDnode){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");

  Message gotMessage("anotherPID", "GOT", "sensorName", json({
    {"value", 1}
  }));
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &gotMessage);
    ASSERT_EQ(PID.getLastSensorReading(), 0);
  );
}

TEST(PIDnode, doesNotAcceptMalformedGOT){
  StrictMock<MockHub> mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 0, 0, 0, 0);
  PID.setName("PID");

  Message gotMessage("PID", "GOT", "sensorName", json({
    {"data", "something"}
  }));
  ASSERT_NO_THROW(
    PID.process(&mockHub, &connectionName, &gotMessage);
    ASSERT_EQ(PID.getLastSensorReading(), 0);
  );
}

TEST(PIDnode, calculatesCorrectionValueCorrectlyOverTime){
  MockHub mockHub;
  std::string connectionName = "connection";
  PIDnode PID("sensorName", "actuatorName", 10, 20, 30, 5);
  PID.setName("PID");
  PID.enable();

  EXPECT_CALL(mockHub, send("LOCAL", Message("sensorName", "GET", "PID"))).Times(4);

  // first iteration
  //Message gotMessage("PID", "GOT", "sensorName", json({{"value", 15}}));
  //PID.process(&mockHub, &connectionName, &gotMessage);
  PID.setSensorValue(15);
  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "SET", "PID", json({
    {"correctionValue",
      (15 - 5) * 10 // P
      + (15 - 5) * 20 // I
      + (15 - 5) * 30 // D
    }
  }))));
  ASSERT_NO_THROW(
    PID.update(&mockHub);
  );

  // second iteration
  PID.setSensorValue(10);
  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "SET", "PID", json({
    {"correctionValue",
      (10 - 5) * 10 // P
      + ((15 - 5) + (10 - 5)) * 20 // I
      + ((10 - 5) - (15 - 5)) * 30 // D
    }
  }))));
  ASSERT_NO_THROW(
    PID.update(&mockHub);
  );

  // third iteration
  PID.setSensorValue(-5);
  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "SET", "PID", json({
    {"correctionValue",
      (-5 - 5) * 10 // P
      + ((15 - 5) + (10 - 5) + (-5 - 5)) * 20 // I
      + ((-5 - 5) - (10 - 5)) * 30 // D
    }
  }))));
  ASSERT_NO_THROW(
    PID.update(&mockHub);
  );

  // forth iteration
  PID.setSensorValue(0);
  EXPECT_CALL(mockHub, send("LOCAL", Message("actuatorName", "SET", "PID", json({
    {"correctionValue",
      (0 - 5) * 10 // P
      + ((15 - 5) + (10 - 5) + (-5 - 5) + (0 - 5)) * 20 // I
      + ((0 - 5) - (-5 - 5)) * 30 // D
    }
  }))));
  ASSERT_NO_THROW(
    PID.update(&mockHub);
  );
}
