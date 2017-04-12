//
// Created by Kyler Jensen on 3/28/17.
//

#include "../include/camera_frame/RGBCameraFrame.h"

using namespace slam;

RGBCameraFrame::RGBCameraFrame(const cv::Mat &data, const chrono& timestamp)
        : ICameraFrameCVMatBased(data, timestamp) {}

RGBCameraFrame::RGBCameraFrame(int rows, int cols, const chrono& timestamp)
        : ICameraFrameCVMatBased(rows, cols, CV_8UC3, cv::Scalar(0, 0, 0), timestamp) {}

RGBCameraFrame::RGBCameraFrame(const std::vector<std::vector<RGBColor>> &data, const chrono& timestamp)
        : ICameraFrameCVMatBased(get_rows(data), get_cols(data), CV_8UC3, cv::Scalar(0, 0, 0), timestamp) { loadFromVector(data); }

void RGBCameraFrame::setPixel(int row, int col, const RGBColor& value) {
    auto &pixel = data.at<cv::Vec3b>(row, col);
    pixel[2] = value.red;
    pixel[1] = value.green;
    pixel[0] = value.blue;
}

RGBColor RGBCameraFrame::getPixel(int row, int col) const {
    auto pixel = data.at<cv::Vec3b>(row, col);
    auto r = pixel[2];
    auto g = pixel[1];
    auto b = pixel[0];
    return { r, g, b };
}
