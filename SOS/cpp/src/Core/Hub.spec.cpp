#include "gtest/gtest.h"
#include "Hub.hpp"
#include "Connection.mock.hpp"
#include "Node.mock.hpp"

using ::testing::Return;
using ::testing::_;

class AutoExitNode : public Node{
public:
  void update(IHub* hub) { hub->exit(); }
  void process(IHub* hub, std::string* connection, Message* message) { }
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
  Message message("target", "type", "sender", json("data"));
  Hub hub("test");

  hub.connect("connection_name", &connection);
  EXPECT_CALL(connection, send(message.toJsonString()));
  hub.send("connection_name", message);
  EXPECT_ANY_THROW(hub.send("other_connection", message));
}

TEST(Hub, exit){
  Hub hub("test");
  AutoExitNode exitNode;

  hub.use("exit", &exitNode);
  hub.listen();
  EXPECT_TRUE(true);
}

TEST(Hub, listen){
  Message message("target", "type", "sender", json("data"));
  MockConnection connection;
  MockNode node;
  Hub hub("test");
  AutoExitNode exitNode;
  std::queue<std::string> json;
  json.push(message.toJsonString());
  ON_CALL(connection, read()).WillByDefault(Return(json));

  EXPECT_CALL(node, setName("node"));
  EXPECT_CALL(node, update(_));
  EXPECT_CALL(node, process(_,_,_));
  EXPECT_CALL(connection, read()).Times(1);
  hub.use("node", &node);
  hub.use("exit", &exitNode);
  hub.connect("connection", &connection);
  hub.listen();
}

TEST(Hub, listen_malformedMessage){
  MockConnection connection;
  MockNode node;
  Hub hub("test");
  AutoExitNode exitNode;
  std::queue<std::string> json;
  json.push(nlohmann::json({{"target", "bob"}}).dump());
  ON_CALL(connection, read()).WillByDefault(Return(json));

  EXPECT_CALL(node, setName("node"));
  EXPECT_CALL(node, update(_));
  //EXPECT_CALL(node, process(_,_,_));
  EXPECT_CALL(connection, read()).Times(1);
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

TEST(Hub, logError){
  Message message("logger", "LOG_ERROR", "test", json("error message"));
  Hub hub("test");
  MockConnection connection;
  hub.connect("connection", &connection);
  hub.setLogger("connection", "logger");
  EXPECT_CALL(connection, send(message.toJsonString()));
  hub.logError("error message");
}

TEST(Hub, logError_notSet){
  Hub hub("test");
  EXPECT_NO_THROW(hub.logError("error message"));
}
