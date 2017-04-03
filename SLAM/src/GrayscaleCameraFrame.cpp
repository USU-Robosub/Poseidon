//
// Created by Kyler Jensen on 3/28/17.
//

#include "../include/camera_frame/GrayscaleCameraFrame.h"

using namespace slam;

GrayscaleCameraFrame::GrayscaleCameraFrame(const cv::Mat &data, const chrono &timestamp)
        : ICameraFrameCVMatBased(data, timestamp) {}

GrayscaleCameraFrame::GrayscaleCameraFrame(int rows, int cols, const chrono& timestamp)
        : ICameraFrameCVMatBased(rows, cols, CV_8U, cv::Scalar(0), timestamp) {}

GrayscaleCameraFrame::GrayscaleCameraFrame(const std::vector<std::vector<uchar>>& data, const chrono& timestamp)
        : ICameraFrameCVMatBased(get_rows(data), get_cols(data), CV_8U, cv::Scalar(0), timestamp) { loadFromVector(data); }

void GrayscaleCameraFrame::setPixel(int row, int col, const uchar& value) {
    data.at<uchar>(row, col) = value;
}

uchar GrayscaleCameraFrame::getPixel(int row, int col) const {
    return data.at<uchar>(row, col);
}


