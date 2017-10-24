#include "gtest/gtest.h"
#include "Router.hpp"
#include "Hub.mock.hpp"

using ::testing::Return;
using ::testing::StrictMock;

TEST(Router, update){
  Message Iexist("router", "I_EXIST", "router", json({
    {"hub", "MockHub"},
    {"nodes", {"node"}}
  }));

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
  EXPECT_CALL(hub, send("connection", Iexist));
  router.setName("router");
  router.update(&hub);
}

TEST(Router, iExist){
  Message Iexist("router", "I_EXIST", "router", json({
    {"hub", "MockHub"},
    {"nodes", {"router", "node"}}
  }));
  Message IexistOther("router", "I_EXIST", "router", json({
    {"hub", "otherHub"},
    {"nodes", {"otherNode"}}
  }));

  std::string connectionName = "connection";
  MockHub hub;
  Router router;
  std::vector<std::string> connectionNames, nodeNames;
  connectionNames.push_back("connection");
  connectionNames.push_back("otherConnection");
  nodeNames.push_back("router");
  nodeNames.push_back("node");
  ON_CALL(hub, getConnectionNames()).WillByDefault(Return(connectionNames));
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));
  ON_CALL(hub, getName()).WillByDefault(Return("MockHub"));

  EXPECT_CALL(hub, getConnectionNames());
  EXPECT_CALL(hub, getNodeNames()).Times(2);
  EXPECT_CALL(hub, getName());
  EXPECT_CALL(hub, send("connection", Iexist));
  EXPECT_CALL(hub, send("otherConnection", IexistOther));
  router.setName("router");
  router.process(&hub, &connectionName, &IexistOther);
}

TEST(Router, process_localNode){
  std::string connectionName = "connection";
  Message messageForNode("node", "something", "someone", json("data"));
  StrictMock<MockHub> hub;
  Router router;
  std::vector<std::string> nodeNames;
  nodeNames.push_back("node");
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));

  EXPECT_CALL(hub, getNodeNames());
  router.process(&hub, &connectionName, &messageForNode);
}

TEST(Router, forward){
  std::string connectionName = "connection";
  Message randomMessage("someone", "something", "someone_else", json("data"));
  MockHub hub;
  std::map<std::string, std::string> allHubs, allNodes;
  allHubs["otherHub"] = "other_connection";
  allNodes["someone"] = "otherHub";
  Router router(allHubs, allNodes);
  std::vector<std::string> nodeNames;
  nodeNames.push_back("node");
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));

  EXPECT_CALL(hub, getNodeNames());
  EXPECT_CALL(hub, send("other_connection", randomMessage));
  router.process(&hub, &connectionName, &randomMessage);
}

TEST(Router, forward_unkown){
  std::string connectionName = "connection";
  Message randomMessage("someone", "something", "someone_else", json("data"));
  Message routeError("someone_else", "ROUTE_NOT_FOUND", "router", json({{"target", "someone"}}));
  MockHub hub;
  Router router;
  router.setName("router");
  std::vector<std::string> nodeNames;
  nodeNames.push_back("node");
  ON_CALL(hub, getNodeNames()).WillByDefault(Return(nodeNames));
  ON_CALL(hub, getName()).WillByDefault(Return("MockHub"));

  EXPECT_CALL(hub, getNodeNames());
  EXPECT_CALL(hub, getName());
  EXPECT_CALL(hub, send("connection", routeError));
  EXPECT_CALL(hub, logError("Route not found to \"someone\" from \"MockHub\""));
  router.process(&hub, &connectionName, &randomMessage);
}
