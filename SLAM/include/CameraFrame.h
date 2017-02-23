//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_CAMERAFRAME_H
#define SLAM_CAMERAFRAME_H

#include "_tmp.h"
#include "RGBColor.h"
#include <vector>

namespace slam {

    struct CameraFrame {

        const Chrono timestamp;
        const std::vector<std::vector<RGBColor>> data;

    };

}



#endif //SLAM_CAMERAFRAME_H
