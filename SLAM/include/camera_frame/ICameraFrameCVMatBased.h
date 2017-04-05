//
// Created by Kyler Jensen on 3/29/17.
//

#ifndef SLAM_ICAMERAFRAMECVMATBASED_H
#define SLAM_ICAMERAFRAMECVMATBASED_H

#include "TCameraFrame.h"
#include "ColorSpace.h"

namespace slam {

    class ICameraFrameCVMatBased : public ICameraFrame {

    protected:
        cv::Mat data;

        ICameraFrameCVMatBased(int rows, int cols, int mode, const cv::Scalar& fill, const chrono& timestamp);

        ICameraFrameCVMatBased(const cv::Mat& data, const chrono& timestamp);

    public:
        int getRows() const override;

        int getCols() const override;

        const cv::Mat &toMat() const override;

        ColorSpace getColorSpace() const override;

    };

}

#endif //SLAM_ICAMERAFRAMECVMATBASED_H
