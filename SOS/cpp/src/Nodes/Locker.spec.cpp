#include "gtest/gtest.h"
#include "Locker.hpp"
#include "Hub.mock.hpp"

using ::testing::_;
using ::testing::NiceMock;

TEST(Locker, nodeCanBeLocked){
  MockHub mockHub;
  std::string connectionName = "connection";
  auto UUIDgenerator = []() -> std::string { return "xxxxx"; };
  Locker locker(UUIDgenerator);
  locker.setName("locker");

  Message lockMessage = Message().to("anotherNode").ofType("lock").from("locker").withData(json({
    {"key", "xxxxx"}
  }));
  Message grantLockMessage = Message().to("test").ofType("grantLock").from("locker").withData(json({
    {"key", "xxxxx"},
    {"node", "anotherNode"}
  }));
  EXPECT_CALL(mockHub, send("LOCAL", lockMessage));
  EXPECT_CALL(mockHub, send(connectionName, grantLockMessage));

  Message getLockMessage = Message().to("locker").ofType("getLock").from("test").withData(json({
    {"node", "anotherNode"}
  }));
  ASSERT_NO_THROW(
    locker.process(&mockHub, &connectionName, &getLockMessage)
  );
}

TEST(Locker, ignoresMalformedLockMessage){
  DummyHub dummyHub;
  std::string connectionName = "conenction";
  auto UUIDgenerator = []() -> std::string { return "xxxxx"; };
  Locker locker(UUIDgenerator);
  locker.setName("locker");

  Message malformedGetLockMessage = Message().to("locker").ofType("getLock").from("test").withData(json({
    {"data", "something"}
  }));
  ASSERT_NO_THROW(
    locker.process(&dummyHub, &connectionName, &malformedGetLockMessage)
  );
}

TEST(Locker, canUnlockLockedNode){
  NiceMock<MockHub> mockHub;
  std::string connectionName = "connection";
  auto UUIDgenerator = []() -> std::string { return "xxxxx"; };
  Locker locker(UUIDgenerator);
  locker.setName("locker");
  Message getLockMessage("locker", "getLock", "test", json({{"node", "anotherNode"}}));
  locker.process(&mockHub, &connectionName, &getLockMessage);

  Message unlockMessage = Message().to("anotherNode").ofType("unlock").from("locker").withData(json({
    {"key", "xxxxx"}
  }));
  EXPECT_CALL(mockHub, send("LOCAL", unlockMessage));

  Message releaseLockMessage = Message().to("locker").ofType("releaseLock").from("test").withData(json({
    {"node", "anotherNode"},
    {"key", "xxxxx"}
  }));
  ASSERT_NO_THROW(
    locker.process(&mockHub, &connectionName, &releaseLockMessage)
  );
}

TEST(Locker, ignoresUnlockOfNonLockedNode){
  DummyHub dummyHub;
  std::string connectionName = "connection";
  auto UUIDgenerator = []() -> std::string { return "xxxxx"; };
  Locker locker(UUIDgenerator);
  locker.setName("locker");

  Message releaseLockMessage = Message().to("locker").ofType("releaseLock").from("test").withData(json({
    {"node", "anotherNode"},
    {"key", "xxxxx"}
  }));
  ASSERT_NO_THROW(
    locker.process(&dummyHub, &connectionName, &releaseLockMessage)
  );
}

TEST(Locker, ignoresMalformedUnlock){
  DummyHub dummyHub;
  std::string connectionName = "connection";
  auto UUIDgenerator = []() -> std::string { return "xxxxx"; };
  Locker locker(UUIDgenerator);
  locker.setName("locker");

  Message releaseLockMessage = Message().to("locker").ofType("releaseLock").from("test").withData(json({
    {"data", "something"}
  }));
  ASSERT_NO_THROW(
    locker.process(&dummyHub, &connectionName, &releaseLockMessage)
  );
}

TEST(locker, rejectsLockingNodeAlreadyLocked){
  NiceMock<MockHub> mockHub;
  std::string connectionName = "connection";
  auto UUIDgenerator = []() -> std::string { return "xxxxx"; };
  Locker locker(UUIDgenerator);
  locker.setName("locker");
  Message getLockMessageFromSomeone("locker", "getLock", "someone", json({{"node", "anotherNode"}}));
  locker.process(&mockHub, &connectionName, &getLockMessageFromSomeone);

  Message rejectLockMessage = Message().to("test").ofType("rejectLock").from("locker").withData(json({
    {"node", "anotherNode"}
  }));
  EXPECT_CALL(mockHub, send(connectionName, rejectLockMessage));

  Message getLockMessage = Message().to("locker").ofType("getLock").from("test").withData(json({
    {"node", "anotherNode"}
  }));
  ASSERT_NO_THROW(
    locker.process(&mockHub, &connectionName, &getLockMessage)
  );
}

TEST(locker, updateDoesNothing){
  DummyHub dummyHub;
  Locker locker([]() -> std::string { return ""; });

  ASSERT_NO_THROW(
    locker.update(&dummyHub)
  );
}
