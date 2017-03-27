//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_CAMERAFRAME_H
#define SLAM_CAMERAFRAME_H

#include "_tmp.h"
#include "RGBColor.h"
#include <vector>

namespace slam {

    class CameraFrame {

    private:
        Chrono timestamp;
        std::vector<std::vector<RGBColor>> data;

    public:
        CameraFrame(unsigned long width, unsigned long height, Chrono timestamp);
        CameraFrame(unsigned long width, unsigned long height);
        Chrono getTimestamp();
        RGBColor getPixel(unsigned long x, unsigned long y);
        void setPixel(unsigned long x, unsigned long y, RGBColor pixel);

    };

}



#endif //SLAM_CAMERAFRAME_H
