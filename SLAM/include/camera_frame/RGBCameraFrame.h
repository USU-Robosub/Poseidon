//
// Created by Kyler Jensen on 3/28/17.
//

#ifndef SLAM_RGBCAMERAFRAME_H
#define SLAM_RGBCAMERAFRAME_H


#include "RGBColor.h"
#include "ICameraFrameCVMatBased.h"

namespace slam {

    class RGBCameraFrame : public TCameraFrame<RGBColor>,
                           public ICameraFrameCVMatBased {

    public:
        RGBCameraFrame(int rows, int cols, const chrono &timestamp);

        RGBCameraFrame(const std::vector<std::vector<RGBColor>> &data, const chrono &timestamp);

        RGBCameraFrame(const cv::Mat &data, const chrono &timestamp);

        void setPixel(int row, int col, const RGBColor &value) override;

        RGBColor getPixel(int row, int col) const override;

    };

}

#endif //SLAM_RGBCAMERAFRAME_H
