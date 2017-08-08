#include <regex>
#include "gtest/gtest.h"
#include "PseudoGUID.hpp"

TEST(PseudoGUID, toHex){
  EXPECT_EQ(toHex(5), "5");
  EXPECT_EQ(toHex(255), "ff");
}

TEST(PseudoGUID, endSlice){
  EXPECT_EQ(endSlice("123456789", 2), "89");
  EXPECT_EQ(endSlice("123456789", 5), "56789");
}

TEST(PseudoGUID, chr4){
  auto regex = "^[0-9a-f]{4}$";
  EXPECT_EQ(chr4().length(), 4);
  EXPECT_TRUE(std::regex_match(chr4(), std::regex(regex)));
}

TEST(PseudoGUID, chr8){
  auto regex = "^[0-9a-f]{8}$";
  EXPECT_EQ(chr8().length(), 8);
  EXPECT_TRUE(std::regex_match(chr8(), std::regex(regex)));
}

TEST(PseudoGUID, chr12){
  auto regex = "^[0-9a-f]{12}$";
  EXPECT_EQ(chr12().length(), 12);
  EXPECT_TRUE(std::regex_match(chr12(), std::regex(regex)));
}


TEST(PseudoGUID, generateUUID){
  auto regex = "^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$";
  EXPECT_EQ(generateUUID().length(), 36);
  EXPECT_TRUE(std::regex_match(generateUUID(), std::regex(regex)));
}
