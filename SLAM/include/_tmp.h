//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_EXTRAS_H
#define SLAM_EXTRAS_H

#include <chrono>
#include <thread>

namespace slam {

    typedef std::tuple<double, double, double> Vector3;
    typedef std::tuple<double, double, double, double> Quaternion;

    using Chrono = std::chrono::steady_clock::time_point;

    class Output3DWrapper {}; //TODO: remove this and replace usages with the real dso::Output3DWrapper

    struct Mat {}; //TODO: remove this and replace usages with the real cv::Mat

}

#endif //SLAM_EXTRAS_H
