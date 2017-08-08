#include "gtest/gtest.h"
#include "Router.hpp"
#include "Hub.mock.hpp"

using ::testing::Return;
using ::testing::StrictMock;

TEST(Router, update){
  MockHub hub;
  Router router;
  std::vector<std::string> connectionNames, nodeNames;
  connectionNames.push_back("connection");
  nodeNames.push_back("node");
  ON_CALL(hub, getConnectionNames()).WillByDefault(Return(connectionNames));
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));
  ON_CALL(hub, getName()).WillByDefault(Return("MockHub"));
  EXPECT_CALL(hub, getConnectionNames());
  EXPECT_CALL(hub, getNodeNames());
  EXPECT_CALL(hub, getName());
  EXPECT_CALL(hub, send("connection", json({
    {"target", "router"},
    {"type", "I_EXIST"},
    {"from", "router"},
    {"data", {
      {"hub", "MockHub"},
      {"nodes", {"node"}}
    }}
  }).dump()));
  router.setName("router");
  router.update(&hub);
}

TEST(Router, process_I_EXSIST){
  MockHub hub;
  Router router;
  std::vector<std::string> connectionNames, nodeNames;
  connectionNames.push_back("connection");
  connectionNames.push_back("otherConnection");
  nodeNames.push_back("router");
  nodeNames.push_back("node");
  auto iExist = json({
    {"target", "router"},
    {"type", "I_EXIST"},
    {"from", "router"},
    {"data", {
      {"hub", "otherHub"},
      {"nodes", {"otherNode"}}
    }}
  });
  ON_CALL(hub, getConnectionNames()).WillByDefault(Return(connectionNames));
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));
  ON_CALL(hub, getName()).WillByDefault(Return("MockHub"));
  EXPECT_CALL(hub, getConnectionNames());
  EXPECT_CALL(hub, getNodeNames());
  EXPECT_CALL(hub, getName());
  EXPECT_CALL(hub, send("connection", json({
    {"target", "router"},
    {"type", "I_EXIST"},
    {"from", "router"},
    {"data", {
      {"hub", "MockHub"},
      {"nodes", {"router", "node"}}
    }}
  }).dump()));
  EXPECT_CALL(hub, send("otherConnection", iExist.dump()));
  router.setName("router");
  router.process(&hub, "connection", iExist);
}

TEST(Router, process_other){
  StrictMock<MockHub> hub;
  Router router;
  std::vector<std::string> nodeNames;
  nodeNames.push_back("node");
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));
  EXPECT_CALL(hub, getNodeNames());
  router.process(&hub, "connection", json({
    {"target", "node"},
  }));
}

TEST(Router, process_anotherHub){
  MockHub hub;
  Router router;
  std::vector<std::string> nodeNames;
  nodeNames.push_back("node");
  auto message = json({
    {"target", "anotherHub"}
  });
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));
  EXPECT_CALL(hub, getNodeNames());
  EXPECT_CALL(hub, send("", message.dump()));
  router.process(&hub, "connection", message);
}
