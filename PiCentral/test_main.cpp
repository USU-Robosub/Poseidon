#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <opencv2/opencv.hpp>

TEST(PiVision, IsIncluded) {
	cv::Mat frame;
}

int main(int argc, char** argv){
  ::testing::InitGoogleMock(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
