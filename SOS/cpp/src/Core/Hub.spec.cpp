#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Hub.hpp"

class MockNode : public Node{
public:
  MOCK_METHOD1(setName, void(std::string));
  MOCK_METHOD1(update, void(IHub*));
  MOCK_METHOD3(process, void(IHub*, std::string, json));
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
