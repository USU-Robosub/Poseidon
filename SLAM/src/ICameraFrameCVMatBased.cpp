//
// Created by Kyler Jensen on 3/29/17.
//

#include "../include/camera_frame/ICameraFrameCVMatBased.h"

using namespace slam;

ICameraFrameCVMatBased::ICameraFrameCVMatBased(int rows, int cols, int mode, const cv::Scalar &fill, const chrono &timestamp)
        : ICameraFrame(timestamp),
          data(cv::Mat(rows, cols, mode, fill)) {}

ICameraFrameCVMatBased::ICameraFrameCVMatBased(const cv::Mat &data, const chrono &timestamp)
        : ICameraFrame(timestamp),
          data(data) {}

int ICameraFrameCVMatBased::getRows() const {
    return data.rows;
}

int ICameraFrameCVMatBased::getCols() const {
    return data.cols;
}

const uchar* ICameraFrameCVMatBased::getData() const {
    return data.data;
}

ColorSpace ICameraFrameCVMatBased::getColorSpace() const {
    return (ColorSpace) data.channels();
}
