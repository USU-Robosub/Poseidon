//
// Created by Kyler Jensen on 3/28/17.
//

#include <opencv2/opencv.hpp>
#include <catch.hpp>
#include "../_config.h"
#include "../../include/camera_frame/RGBCameraFrame.h"

using namespace slam;

std::vector<RGBColor> expected_colors_by_row = {
        { 255,  0,    0   },
        { 0,    255,  0   },
        { 0,    0,    255 },
        { 100,  100,  100 },
        { 0,    0,    0   },
        { 255,  255,  255 },
        { 120,  210,  212 },
        { 255,  255,  255 },
        { 255,  255,  255 },
        { 255,  255,  255 },
};

void test_exact_match_rgb(std::string filename) {
    auto img = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
    auto frame = RGBCameraFrame(img, std::chrono::steady_clock::now());
    REQUIRE(frame.getRows() == 10);
    REQUIRE(frame.getCols() == 10);
    REQUIRE(frame.getColorSpace() == RGB);
    for (auto row = 0; row < frame.getRows(); row++) {
        for (auto col = 0; col < frame.getCols(); col++) {
            auto expected = expected_colors_by_row[row];
            auto actual = frame.getPixel(row, col);
            REQUIRE(actual == expected);
        }
    }
}

void test_near_match_rgb(std::string filename) {
    auto img = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
    auto frame = RGBCameraFrame(img, std::chrono::steady_clock::now());
    REQUIRE(frame.getRows() == 10);
    REQUIRE(frame.getCols() == 10);
    REQUIRE(frame.getColorSpace() == RGB);
    for (auto row = 0; row < frame.getRows(); row++) {
        for (auto col = 0; col < frame.getCols(); col++) {
            auto expected = expected_colors_by_row[row];
            auto actual = frame.getPixel(row, col);
            REQUIRE(actual.almostEquals(expected));
        }
    }
}

TEST_CASE("RGBCameraFrame can be initialized with a real cv::Mat") {
    SECTION("Works with a real .bmp file") {
        auto filename = TestConfig::testResourcesDirectory() + "/RGB10x10.bmp";
        test_exact_match_rgb(filename);
    }
    SECTION("Works with a real .png file") {
        auto filename = TestConfig::testResourcesDirectory() + "/RGB10x10.png";
        test_exact_match_rgb(filename);
    }
    SECTION("Works with a real .jpg file") {
        auto filename = TestConfig::testResourcesDirectory() + "/RGB10x10.jpg";
        test_near_match_rgb(filename);
    }
}
