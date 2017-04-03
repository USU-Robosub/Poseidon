//
// Created by Kyler Jensen on 2/28/17.
//

#include <opencv2/opencv.hpp>
#include <catch.hpp>
#include "../../include/camera_frame/RGBCameraFrame.h"

using namespace slam;

TEST_CASE("TCameraFrame can be instantiated with a 2D vector of RGB") {
    SECTION("A dense RGB vector works as expected") {
        std::vector<std::vector<RGBColor>> data = {
                {{255, 254, 253}, {252, 251, 250}},
                {{249, 248, 247}, {246, 245, 244}}
        };
        auto frame = RGBCameraFrame(data, std::chrono::steady_clock::now());
        REQUIRE(frame.getRows() == 2);
        REQUIRE(frame.getCols() == 2);
        REQUIRE(frame.getColorSpace() == RGB);
        REQUIRE(frame.getPixel(0, 0) == data[0][0]);
        REQUIRE(frame.getPixel(0, 1) == data[0][1]);
        REQUIRE(frame.getPixel(1, 0) == data[1][0]);
        REQUIRE(frame.getPixel(1, 1) == data[1][1]);
    }
    SECTION("A ragged RGB vector is padded with black pixels") {
        std::vector<std::vector<RGBColor>> data = {
                {{255, 254, 253}},
                {{249, 248, 247}, {246, 245, 244}},
                {{243, 242, 241}, {240, 239, 238}, {237, 236, 235}}
        };
        RGBColor BLACK = { 0, 0, 0 };
        auto frame = RGBCameraFrame(data, std::chrono::steady_clock::now());
        REQUIRE(frame.getRows() == 3);
        REQUIRE(frame.getCols() == 3);
        REQUIRE(frame.getColorSpace() == RGB);
        REQUIRE(frame.getPixel(0, 0) == data[0][0]);
        REQUIRE(frame.getPixel(0, 1) == BLACK);
        REQUIRE(frame.getPixel(0, 2) == BLACK);
        REQUIRE(frame.getPixel(1, 0) == data[1][0]);
        REQUIRE(frame.getPixel(1, 1) == data[1][1]);
        REQUIRE(frame.getPixel(1, 2) == BLACK);
        REQUIRE(frame.getPixel(2, 0) == data[2][0]);
        REQUIRE(frame.getPixel(2, 1) == data[2][1]);
        REQUIRE(frame.getPixel(2, 2) == data[2][2]);
    }
    SECTION("An empty RGB vector produces an empty TCameraFrame") {
        std::vector<std::vector<RGBColor>> data = {};
        auto frame = RGBCameraFrame(data, std::chrono::steady_clock::now());
        REQUIRE(frame.getRows() == 0);
        REQUIRE(frame.getCols() == 0);
        REQUIRE(frame.getColorSpace() == RGB);
    }
}
