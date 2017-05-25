//
// Created by Kyler Jensen on 3/28/17.
//

#ifndef SLAM_GRAYSCALECAMERAFRAME_H
#define SLAM_GRAYSCALECAMERAFRAME_H


#include "../_types.h"
#include "ICameraFrameCVMatBased.h"

namespace slam {

    class GrayscaleCameraFrame : public TCameraFrame<uchar>,
                                 public ICameraFrameCVMatBased {

    public:
        GrayscaleCameraFrame(int rows, int cols, const chrono& timestamp);

        GrayscaleCameraFrame(const cv::Mat& data, const chrono& timestamp);

        GrayscaleCameraFrame(const std::vector<std::vector<uchar>>& data, const chrono& timestamp);

        void setPixel(int row, int col, const uchar& value) override;

        uchar getPixel(int row, int col) const override;

    };

}

#endif //SLAM_GRAYSCALECAMERAFRAME_H
