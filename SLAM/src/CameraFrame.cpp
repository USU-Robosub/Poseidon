//
// Created by Kyler Jensen on 2/28/17.
//

#include "../include/CameraFrame.h"

namespace slam {

    CameraFrame::CameraFrame(unsigned short width, unsigned short height, Chrono timestamp) {
        this->timestamp = timestamp;
        this->data.resize(height);
        for(unsigned short i = 0; i < height; i++) {
            this->data[i].resize(width);
        }
    }

    CameraFrame::CameraFrame(unsigned short width, unsigned short height):
            CameraFrame(width, height, std::chrono::steady_clock::now()) {
    }

    void CameraFrame::setPixel(unsigned short x, unsigned short y, RGBColor pixel) {
        data[y][x] = pixel;
    }

    RGBColor CameraFrame::getPixel(unsigned short x, unsigned short y) {
        return data[y][x];
    }

    Chrono CameraFrame::getTimestamp() {
        return timestamp;
    }

}

