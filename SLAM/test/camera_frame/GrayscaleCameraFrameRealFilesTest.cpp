//
// Created by Kyler Jensen on 3/28/17.
//

#include <opencv2/opencv.hpp>
#include <catch.hpp>
#include "../_config.h"
#include "../../include/camera_frame/GrayscaleCameraFrame.h"

using namespace slam;

std::vector<uchar> expected_intensities_by_row = {
        54,
        182,
        18,
        100,
        0,
        255,
        191,
        255,
        255,
        255
};

void test_exact_match_gs(std::string filename) {
    auto img = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    auto frame = GrayscaleCameraFrame(img, std::chrono::steady_clock::now());
    REQUIRE(frame.getRows() == 10);
    REQUIRE(frame.getCols() == 10);
    REQUIRE(frame.getColorSpace() == GRAYSCALE);
    for (auto row = 0; row < frame.getRows(); row++) {
        for (auto col = 0; col < frame.getCols(); col++) {
            auto expected = expected_intensities_by_row[row];
            auto actual = frame.getPixel(row, col);
            REQUIRE((int)actual == (int)expected);
        }
    }
}

void test_near_match_gs(std::string filename) {
    auto img = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    auto frame = GrayscaleCameraFrame(img, std::chrono::steady_clock::now());
    REQUIRE(frame.getRows() == 10);
    REQUIRE(frame.getCols() == 10);
    REQUIRE(frame.getColorSpace() == GRAYSCALE);
    for (auto row = 0; row < frame.getRows(); row++) {
        for (auto col = 0; col < frame.getCols(); col++) {
            auto expected = expected_intensities_by_row[row];
            auto actual = frame.getPixel(row, col);
            REQUIRE((int)expected - (int)actual <  2);
            REQUIRE((int)expected - (int)actual > -2);
        }
    }
}

TEST_CASE("GrayscaleCameraFrame can be initialized with a real cv::Mat") {
    SECTION("Works with a real .bmp file") {
        auto filename = TestConfig::testResourcesDirectory() + "/GRAYSCALE10x10.bmp";
        test_exact_match_gs(filename);
    }
    SECTION("Works with a real .png file") {
        auto filename = TestConfig::testResourcesDirectory() + "/GRAYSCALE10x10.png";
        test_exact_match_gs(filename);
    }
    SECTION("Works with a real .jpg file") {
        auto filename = TestConfig::testResourcesDirectory() + "/GRAYSCALE10x10.jpg";
        test_near_match_gs(filename);
    }
}
