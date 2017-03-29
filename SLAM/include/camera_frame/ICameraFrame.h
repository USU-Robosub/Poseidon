//
// Created by Kyler Jensen on 3/29/17.
//

#ifndef SLAM_ICAMERAFRAME_H
#define SLAM_ICAMERAFRAME_H

#include <opencv2/opencv.hpp>
#include "ColorSpace.h"
#include "../_types.h"

namespace slam {

    class ICameraFrame {

    protected:
        chrono timestamp;

        ICameraFrame(const chrono &timestamp);

    public:
        const chrono& getTimestamp() const;

        virtual int getRows() const = 0;

        virtual int getCols() const = 0;

        virtual const cv::Mat& toMat() = 0;

        virtual ColorSpace getColorSpace() = 0;

    };

}


#endif //SLAM_ICAMERAFRAME_H
