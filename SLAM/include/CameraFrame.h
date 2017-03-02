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
        CameraFrame(unsigned short width, unsigned short height, Chrono timestamp);
        CameraFrame(unsigned short width, unsigned short height);
        void setPixel(unsigned short, unsigned short y, RGBColor pixel);
        RGBColor getPixel(unsigned short x, unsigned short y);
        Chrono getTimestamp();

    };

}



#endif //SLAM_CAMERAFRAME_H
