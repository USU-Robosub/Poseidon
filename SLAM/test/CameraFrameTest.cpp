//
// Created by Kyler Jensen on 2/28/17.
//

#include "catch.hpp"
#include "../include/CameraFrame.h"

TEST_CASE("CameraFrame works as expected") {

    auto frame = slam::CameraFrame(640, 480);

    for(unsigned long r = 0; r < 640; r++) {
        for(unsigned long c = 0; c < 480; c++) {
            auto pixel = slam::RGBColor();
            pixel.red = 150;
            pixel.green = 110;
            pixel.blue = 120;
            frame.setPixel(r, c, pixel);
        }
    }

    for(unsigned long r = 0; r < 640; r++) {
        for(unsigned long c = 0; c < 480; c++) {
            auto pixel = frame.getPixel(r, c);
            REQUIRE(pixel.red == 150);
            REQUIRE(pixel.green == 110);
            REQUIRE(pixel.blue == 120);
        }
    }

}