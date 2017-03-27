//
// Created by Kyler Jensen on 2/28/17.
//

#include "../include/CameraFrame.h"

namespace slam {

    CameraFrame::CameraFrame(unsigned long width, unsigned long height, Chrono timestamp) {
        this->timestamp = timestamp;
        this->data.resize(height);
        for(unsigned long i = 0; i < height; i++) {
            this->data[i].resize(width);
        }
    }

    CameraFrame::CameraFrame(unsigned long width, unsigned long height):
            CameraFrame(width, height, std::chrono::steady_clock::now()) {
    }

    Chrono CameraFrame::getTimestamp() {
        return timestamp;
    }

    RGBColor CameraFrame::getPixel(unsigned long x, unsigned long y) {
        return data[y][x];
    }

    void CameraFrame::setPixel(unsigned long x, unsigned long y, RGBColor pixel) {
        data[y][x] = pixel;
    }

}

