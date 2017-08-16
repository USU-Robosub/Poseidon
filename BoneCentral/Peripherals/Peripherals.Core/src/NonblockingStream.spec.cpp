#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>
#include "gtest/gtest.h"
#include "NonblockingStream.h"

TEST(NonblockingStream, canRead){
  std::stringstream sstream;
  sstream << "hello";
  sstream.clear();
  NonblockingStream stream(&sstream);
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  EXPECT_EQ(stream.canRead(), true);
  std::cout << "force close" << std::endl;
  stream.stopAfterNextLine();
}
