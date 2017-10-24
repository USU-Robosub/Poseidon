#include "gtest/gtest.h"
#include "Locker.hpp"
#include "Hub.mock.hpp"

using ::testing::_;

TEST(ActuatorLock, process_lock){
  Message requestLock("locker", "LOCK", "locking_node", json({
    {"node", "locked_node"}
  }));
  Message secondRequestLock("locker", "LOCK", "locking_node_2", json({
    {"node", "locked_node"}
  }));
  Message applyLock("locked_node", "APPLY_LOCK", "locker", json({
    {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"}
  }));
  Message grantLock("locking_node", "GRANT_LOCK", "locker", json({
    {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"},
    {"node", "locked_node"}
  }));
  Message rejectLock("locking_node_2", "REJECT_LOCK", "locker", json({
    {"node", "locked_node"}
  }));

  std::string connectionName = "connection_name";
  MockHub hub;
  Locker locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });
  locker.setName("locker");

  EXPECT_CALL(hub, send("LOCAL", applyLock));
  EXPECT_CALL(hub, send("connection_name", grantLock));
  locker.process(&hub, &connectionName, &requestLock);

  EXPECT_CALL(hub, send("connection_name", rejectLock));
  locker.process(&hub, &connectionName, &secondRequestLock);
}

TEST(ActuatorLock, process_unlock){
  Message requestLock("locker", "LOCK", "locking_node", json({
    {"node", "locked_node"}
  }));
  Message removeLock("locked_node", "REMOVE_LOCK", "locker", json({
    {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"}
  }));
  Message requestUnlock("locker", "UNLOCK", "locking_node", json({
    {"node", "locked_node"},
    {"key", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"},
  }));

  std::string connectionName = "connection_name";
  MockHub hub;
  Locker locker([]() -> std::string { return "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"; });
  locker.setName("locker");

  EXPECT_CALL(hub, send(_, _)).Times(2);
  locker.process(&hub, &connectionName, &requestLock);

  EXPECT_CALL(hub, send("LOCAL", removeLock));
  locker.process(&hub, &connectionName, &requestUnlock);
}
