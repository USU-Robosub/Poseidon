//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_OPENCV_MAT_H
#define SLAM_OPENCV_MAT_H

#include "../slam.h"

using namespace slam;

/**
 * In the future, this can likely be changed to a type alias for OpenCV_Mat. If so, it can be placed
 * in ../slam.h alongside Timestamp. This struct represents an OpenCV n-dimensional dense array
 * (a.k.a. an "image").
 * @see <a href='http://docs.opencv.org/2.4.10/modules/core/doc/basic_structures.html#mat'>
 * http://docs.opencv.org/2.4.10/modules/core/doc/basic_structures.html#mat
 * </a>
 * */
struct CameraFrame {
    //TODO
};

#endif //SLAM_OPENCV_MAT_H
