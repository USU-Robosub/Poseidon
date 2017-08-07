#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ActuatorLock.hpp"

using ::testing::_;

class MockHub : public IHub{
public:
  MOCK_METHOD5(send, void(std::string, std::string, std::string, std::string, std::string));
  MOCK_METHOD4(send, void(std::string, std::string, std::string, std::string));
  MOCK_METHOD3(send, void(std::string, std::string, std::string));
  MOCK_METHOD1(error, void(std::string));
  MOCK_METHOD2(lock, void(std::string, std::string));
};

TEST(ActuatorLock, process_lock){
  MockHub hub;
  ActuatorLock locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });
  locker.setName("locker");

  EXPECT_CALL(hub, send("locker", "target_hub", "target_node", json({
    {"type", "APPLY_LOCK"},
    {"lock", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"},
  }).dump()));
  EXPECT_CALL(hub, send("locker", "test_hub", "test_node", json({
    {"type", "GRANT_LOCK"},
    {"hub", "target_hub"},
    {"node", "target_node"},
    {"lock", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"},
  }).dump()));

  locker.process(&hub, json({
    {"from", {
      {"hub", "test_hub"},
      {"node", "test_node"}
    }},
    {"to", {
      {"hub", "master"},
      {"node", "ACTUATOR_LOCK"}
    }},
    {"request", {
      {"type", "LOCK"},
      {"hub", "target_hub"},
      {"node", "target_node"}
    }}
  }));

  EXPECT_CALL(hub, send("locker", "test2_hub", "test2_node", json({
    {"type", "REJECT_LOCK"},
    {"hub", "target_hub"},
    {"node", "target_node"},
  }).dump()));

  locker.process(&hub, json({
    {"from", {
      {"hub", "test2_hub"},
      {"node", "test2_node"}
    }},
    {"to", {
      {"hub", "master"},
      {"node", "ACTUATOR_LOCK"}
    }},
    {"request", {
      {"type", "LOCK"},
      {"hub", "target_hub"},
      {"node", "target_node"}
    }}
  }));
}

TEST(ActuatorLock, process_unlock){
  MockHub hub;
  ActuatorLock locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });
  locker.setName("locker");

  EXPECT_CALL(hub, send(_, _, _, _)).Times(2);

  locker.process(&hub, json({
    {"from", {
      {"hub", "test_hub"},
      {"node", "test_node"}
    }},
    {"to", {
      {"hub", "master"},
      {"node", "ACTUATOR_LOCK"}
    }},
    {"request", {
      {"type", "LOCK"},
      {"hub", "target_hub"},
      {"node", "target_node"}
    }}
  }));

  EXPECT_CALL(hub, send("locker", "target_hub", "target_node", json({
    {"type", "REMOVE_LOCK"},
    {"lock", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"},
  }).dump()));

  locker.process(&hub, json({
    {"from", {
      {"hub", "test2_hub"},
      {"node", "test2_node"}
    }},
    {"to", {
      {"hub", "master"},
      {"node", "ACTUATOR_LOCK"}
    }},
    {"request", {
      {"type", "UNLOCK"},
      {"hub", "target_hub"},
      {"node", "target_node"},
      {"lock", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"}
    }}
  }));
}

TEST(ActuatorLock, process_invalid){
  MockHub hub;
  ActuatorLock locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });

  EXPECT_CALL(hub, error(_)).Times(1);

  locker.process(&hub, json({
    {"from", {
      {"hub", "test_hub"},
      {"node", "test_node"}
    }},
    {"to", {
      {"hub", "master"},
      {"node", "ACTUATOR_LOCK"}
    }},
    {"request", {
      {"type", "LOCK_invalid"},
      {"hub", "target_hub"},
      {"node", "target_node"}
    }}
  }));
}
