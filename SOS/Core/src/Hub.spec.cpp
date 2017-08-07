#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Hub.hpp"

class MockNode : public Node{
public:
  MOCK_METHOD1(setName, void(std::string));
  MOCK_METHOD1(update, void(IHub*));
  MOCK_METHOD2(process, void(IHub*, json));
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
  EXPECT_ANY_THROW(hub.use("node", &node2));
}

TEST(Hub, connect){
  MockConnection connection;
  MockConnection connection2;
  Hub hub("test");
  hub.connect("master", &connection);
  EXPECT_ANY_THROW(hub.connect("master", &connection2));
}

TEST(Hub, address){
  Hub hub("test");
  hub.address("master", "sensor");
  EXPECT_NO_THROW(hub.address("master", "sensor2"));
  EXPECT_ANY_THROW(hub.address("other", "sensor"));
}

TEST(Hub, send){
  MockConnection connection;
  Hub hub("test");
  hub.connect("master", &connection);
  EXPECT_CALL(connection, send(json({
    {"from", {
      {"hub", "test"},
      {"node", "node"}
    }},
    {"to", {
      {"hub", "master"},
      {"node", "sensor"}
    }},
    {"request", {
      {"data1", "value1"},
      {"data2", "value2"}
    }}
  }).dump())).Times(2);
  hub.send("master", "node", "master", "sensor", json({
    {"data1", "value1"},
    {"data2", "value2"}
  }).dump());
  hub.send("node", "master", "sensor", json({
    {"data1", "value1"},
    {"data2", "value2"}
  }).dump());
}
