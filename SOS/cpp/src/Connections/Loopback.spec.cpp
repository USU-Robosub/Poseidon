#include "gtest/gtest.h"
#include "Loopback.hpp"

TEST(Loopback, single_message){
  Loopback loop;
  loop.send("test message");
  auto messages = loop.read();
  EXPECT_EQ(messages.size(), 1);
  EXPECT_EQ(messages.front(), "test message");
}

TEST(Loopback, multiple_message){
  Loopback loop;

  loop.send("test message");
  loop.send("test message 2");
  loop.send("test message 3");
  auto messages = loop.read();
  EXPECT_EQ(messages.size(), 3);
  EXPECT_EQ(messages.front(), "test message");
  messages.pop();
  EXPECT_EQ(messages.front(), "test message 2");
  messages.pop();
  EXPECT_EQ(messages.front(), "test message 3");

  loop.send("test message 4");
  loop.send("test message 5");
  messages = loop.read();
  EXPECT_EQ(messages.size(), 2);
  EXPECT_EQ(messages.front(), "test message 4");
  messages.pop();
  EXPECT_EQ(messages.front(), "test message 5");
}
