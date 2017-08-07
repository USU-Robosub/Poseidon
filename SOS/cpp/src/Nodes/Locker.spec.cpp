#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Locker.hpp"

using ::testing::_;

class MockHub : public IHub{
public:
  MOCK_METHOD2(send, void(std::string, std::string));
  MOCK_METHOD0(getName, std::string(void));
  MOCK_METHOD0(getNodeNames, std::vector<std::string>(void));
  MOCK_METHOD0(getConnectionNames, std::vector<std::string>(void));
  MOCK_METHOD0(exit, void(void));
};

TEST(ActuatorLock, process_lock){
  MockHub hub;
  Locker locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });
  locker.setName("locker");

  EXPECT_CALL(hub, send("LOCAL", json({
    {"type", "APPLY_LOCK"},
    {"target", "locked_node"},
    {"from", "locker"},
    {"data", {
      {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"}
    }}
  }).dump()));
  EXPECT_CALL(hub, send("connection_name", json({
    {"type", "GRANT_LOCK"},
    {"target", "locking_node"},
    {"from", "locker"},
    {"data", {
      {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"},
      {"node", "locked_node"}
    }}
  }).dump()));

  locker.process(&hub, "connection_name", json({
    {"target", "locker"},
    {"type", "LOCK"},
    {"from", "locking_node"},
    {"data", {
      {"node", "locked_node"}
    }}
  }));

  EXPECT_CALL(hub, send("connection_name", json({
    {"type", "REJECT_LOCK"},
    {"target", "locking_node_2"},
    {"from", "locker"},
    {"data", {
      {"node", "locked_node"}
    }}
  }).dump()));

  locker.process(&hub, "connection_name", json({
    {"target", "locker"},
    {"type", "LOCK"},
    {"from", "locking_node_2"},
    {"data", {
      {"node", "locked_node"}
    }}
  }));
}

TEST(ActuatorLock, process_unlock){
  MockHub hub;
  Locker locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });
  locker.setName("locker");

  EXPECT_CALL(hub, send(_, _)).Times(2);

  locker.process(&hub, "connection_name", json({
    {"target", "locker"},
    {"type", "LOCK"},
    {"from", "locking_node"},
    {"data", {
      {"node", "locked_node"}
    }}
  }));

  EXPECT_CALL(hub, send("LOCAL", json({
    {"type", "REMOVE_LOCK"},
    {"target", "locked_node"},
    {"from", "locker"},
    {"data", {
      {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"}
    }}
  }).dump()));

  locker.process(&hub, "connection_name", json({
    {"target", "locker"},
    {"type", "UNLOCK"},
    {"from", "locking_node"},
    {"data", {
      {"node", "locked_node"},
      {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"},
    }}
  }));
}

TEST(ActuatorLock, process_invalid){
  MockHub hub;
  Locker locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });

  //EXPECT_CALL(hub, error(_)).Times(1);

  locker.process(&hub, "connection_name", json({
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
