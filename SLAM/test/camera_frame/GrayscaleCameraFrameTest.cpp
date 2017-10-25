//
// Created by Kyler Jensen on 3/29/17.
//

#include <catch.hpp>
#include "../../include/camera_frame/GrayscaleCameraFrame.h"

using namespace slam;

TEST_CASE("TCameraFrame can be instantiated with a 2D vector of uchar") {
    SECTION("A dense uchar vector works as expected") {
        std::vector<std::vector<uchar>> data = {
                {255, 254},
                {253, 252}
        };
        auto frame = GrayscaleCameraFrame(data, std::chrono::steady_clock::now());
        REQUIRE(frame.getRows() == 2);
        REQUIRE(frame.getCols() == 2);
        REQUIRE(frame.getColorSpace() == GRAYSCALE);
        REQUIRE(frame.getPixel(0, 0) == data[0][0]);
        REQUIRE(frame.getPixel(0, 1) == data[0][1]);
        REQUIRE(frame.getPixel(1, 0) == data[1][0]);
        REQUIRE(frame.getPixel(1, 1) == data[1][1]);
    }
    SECTION("A ragged uchar vector is padded with black pixels") {
        std::vector<std::vector<uchar>> data = {
                {255},
                {254, 253},
                {252, 251, 250}
        };
        uchar BLACK = 0;
        auto frame = GrayscaleCameraFrame(data, std::chrono::steady_clock::now());
        REQUIRE(frame.getRows() == 3);
        REQUIRE(frame.getCols() == 3);
        REQUIRE(frame.getColorSpace() == GRAYSCALE);
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
    SECTION("An empty uchar vector produces an empty TCameraFrame") {
        std::vector<std::vector<uchar>> data = {};
        auto frame = GrayscaleCameraFrame(data, std::chrono::steady_clock::now());
        REQUIRE(frame.getRows() == 0);
        REQUIRE(frame.getCols() == 0);
        REQUIRE(frame.getColorSpace() == GRAYSCALE);
    }

}