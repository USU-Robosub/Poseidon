#include "gtest/gtest.h"
#include "Hub.hpp"
#include "Connection.mock.hpp"
#include "Node.mock.hpp"

using ::testing::Return;
using ::testing::_;

class AutoExitNode : public Node{
public:
  void update(IHub* hub) { hub->exit(); }
  void process(IHub* hub, std::string connection, json message) { }
};

TEST(Hub, use){
  MockNode node;
  MockNode node2;
  Hub hub("test");
  EXPECT_CALL(node, setName("node"));
  hub.use("node", &node);
  auto nodeNames = hub.getNodeNames();
  EXPECT_EQ(nodeNames.size(), 1);
  EXPECT_EQ(nodeNames[0], "node");
  EXPECT_ANY_THROW(hub.use("node", &node2));
}

TEST(Hub, connect){
  MockConnection connection;
  MockConnection connection2;
  Hub hub("test");
  hub.connect("master", &connection);
  EXPECT_ANY_THROW(hub.connect("master", &connection2));
}

TEST(Hub, send){
  MockConnection connection;
  Hub hub("test");
  hub.connect("connection_name", &connection);
  EXPECT_CALL(connection, send("test data"));
  hub.send("connection_name", "test data");
  EXPECT_ANY_THROW(hub.send("other_connection", "test data"));
}

TEST(Hub, exit){
  Hub hub("test");
  AutoExitNode exitNode;
  hub.use("exit", &exitNode);
  hub.listen();
  EXPECT_TRUE(true);
}

TEST(Hub, listen){
  MockConnection connection;
  MockNode node;
  AutoExitNode exitNode;
  std::queue<std::string> json;
  json.push(nlohmann::json({{"target", "bob"}}).dump());
  EXPECT_CALL(node, setName("node"));
  EXPECT_CALL(node, update(_));
  EXPECT_CALL(node, process(_,_,_));
  ON_CALL(connection, read()).WillByDefault(Return(json));
  EXPECT_CALL(connection, read()).Times(1);
  Hub hub("test");
  hub.use("node", &node);
  hub.use("exit", &exitNode);
  hub.connect("connection", &connection);
  hub.listen();
}

TEST(Hub, getName){
  Hub hub("test");
  EXPECT_EQ(hub.getName(), "test");
}

TEST(Hub, getNodeNames){
  Hub hub("test");
  MockNode node, node2, node3;
  EXPECT_CALL(node, setName("node"));
  EXPECT_CALL(node2, setName("node2"));
  EXPECT_CALL(node3, setName("node3"));
  hub.use("node", &node);
  hub.use("node2", &node2);
  hub.use("node3", &node3);
  std::vector<std::string> nodeNames = hub.getNodeNames();
  EXPECT_EQ(nodeNames.size(), 3);
  EXPECT_EQ(nodeNames[0], "node");
  EXPECT_EQ(nodeNames[1], "node2");
  EXPECT_EQ(nodeNames[2], "node3");
}

TEST(Hub, getConnectionNames){
  Hub hub("test");
  MockConnection connection, connection2, connection3;
  hub.connect("connection", &connection);
  hub.connect("connection2", &connection2);
  hub.connect("connection3", &connection3);
  std::vector<std::string> connectionNames = hub.getConnectionNames();
  EXPECT_EQ(connectionNames.size(), 3);
  EXPECT_EQ(connectionNames[0], "connection");
  EXPECT_EQ(connectionNames[1], "connection2");
  EXPECT_EQ(connectionNames[2], "connection3");
}
