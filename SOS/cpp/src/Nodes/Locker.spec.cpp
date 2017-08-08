#include "gtest/gtest.h"
#include "Locker.hpp"
#include "Hub.mock.hpp"

using ::testing::_;

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
