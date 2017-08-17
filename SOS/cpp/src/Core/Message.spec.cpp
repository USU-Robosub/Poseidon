#include "gtest/gtest.h"
#include "Message.hpp"

TEST(Message, fromString){
  json rawMessage = json({
    {"target", "target_node"},
    {"type", "action_type"},
    {"sender", "sender_node"},
    {"data", { {"val1", 101}, {"val2", "test"} }}
  });
  Message message(rawMessage.dump());
  EXPECT_EQ(message.getTarget(), rawMessage["target"]);
  EXPECT_EQ(message.getType(), rawMessage["type"]);
  EXPECT_EQ(message.getSender(), rawMessage["sender"]);
  EXPECT_EQ(message.getData(), rawMessage["data"]);
  EXPECT_FALSE(message.isMalformed());
}

TEST(Message, fromString_missingTarget){
  json rawMessage = json({
    {"type", "action_type"},
    {"sender", "sender_node"},
    {"data", { {"val1", 101}, {"val2", "test"} }}
  });
  Message message(rawMessage.dump());
  EXPECT_TRUE(message.isMalformed());
}

TEST(Message, fromString_missingType){
  json rawMessage = json({
    {"target", "target_node"},
    {"sender", "sender_node"},
    {"data", { {"val1", 101}, {"val2", "test"} }}
  });
  Message message(rawMessage.dump());
  EXPECT_TRUE(message.isMalformed());
}

TEST(Message, fromString_missingSender){
  json rawMessage = json({
    {"target", "target_node"},
    {"type", "action_type"},
    {"data", { {"val1", 101}, {"val2", "test"} }}
  });
  Message message(rawMessage.dump());
  EXPECT_TRUE(message.isMalformed());
}

TEST(Message, fromString_missingData){
  json rawMessage = json({
    {"target", "target_node"},
    {"type", "action_type"},
    {"sender", "sender_node"}
  });
  Message message(rawMessage.dump());
  EXPECT_TRUE(message.isMalformed());
}

TEST(Message, fromString_nonJson){
  Message message("Non Json");
  EXPECT_TRUE(message.isMalformed());
}

TEST(Message, fromParts){
  Message message("target", "type", "sender", json({"data"}));
  EXPECT_EQ(message.getTarget(), "target");
  EXPECT_EQ(message.getType(), "type");
  EXPECT_EQ(message.getSender(), "sender");
  EXPECT_EQ(message.getData(), json({"data"}));
  EXPECT_FALSE(message.isMalformed());
}

TEST(Message, isAddressedTo){
  json rawMessage = json({
    {"target", "target_node"},
    {"type", "action_type"},
    {"sender", "sender_node"},
    {"data", { {"val1", 101}, {"val2", "test"} }}
  });
  Message message(rawMessage.dump());
  EXPECT_TRUE(message.isAddressedTo("target_node"));
}

TEST(Message, matchesType){
  json rawMessage = json({
    {"target", "target_node"},
    {"type", "action_type"},
    {"sender", "sender_node"},
    {"data", { {"val1", 101}, {"val2", "test"} }}
  });
  Message message(rawMessage.dump());
  EXPECT_TRUE(message.matchesType("action_type"));
}

TEST(Message, isFrom){
  json rawMessage = json({
    {"target", "target_node"},
    {"type", "action_type"},
    {"sender", "sender_node"},
    {"data", { {"val1", 101}, {"val2", "test"} }}
  });
  Message message(rawMessage.dump());
  EXPECT_TRUE(message.isFrom("sender_node"));
}

TEST(Message, equalsOperator){
  Message message1("target", "type", "sender", json("data"));
  Message message2("target", "type", "sender", json("data"));
  EXPECT_EQ(message1, message2);
}
