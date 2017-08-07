#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Hub.hpp"

using ::testing::Return;
using ::testing::_;

class MockNode : public Node{
public:
  MOCK_METHOD1(setName, void(std::string));
  MOCK_METHOD1(update, void(IHub*));
  MOCK_METHOD3(process, void(IHub*, std::string, json));
};

class AutoExitNode : public Node{
public:
  void update(IHub* hub) { hub->exit(); }
  void process(IHub* hub, std::string connection, json message) { }
};

class MockConnection : public Connection{
public:
  MOCK_METHOD1(send, void(std::string));
  MOCK_METHOD0(read, std::queue<std::string>());
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

TEST(Hub, listen){
  MockConnection connection;
  MockNode node;
  AutoExitNode exitNode;
  std::queue<std::string> json;
  std::string message = nlohmann::json({{"target", "bob"}}).dump();
  json.push(message);
  EXPECT_CALL(node, process(_,_,_));
  ON_CALL(connection, read()).WillByDefault(Return(json));
  Hub hub("test");
  hub.use("node", &node);
  hub.use("exit", &exitNode);
  hub.connect("connection", &connection);
  hub.listen();
}
