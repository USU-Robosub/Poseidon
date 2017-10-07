#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <opencv2/opencv.hpp>
#include <tacopie/tacopie>

TEST(PiVision, IsIncluded) {
	cv::Mat frame;
}

TEST(TacoPie, IsIncluded) {
	tacopie::tcp_client client;
}

int main(int argc, char** argv){
  ::testing::InitGoogleMock(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
