//
// Created by Kyler Jensen on 4/12/17.
//

#ifndef SLAM_CVFRAMESTREAM_H
#define SLAM_CVFRAMESTREAM_H

#include "IFrameStream.h"

namespace slam {

    class CVFrameStream : public IFrameStream {

    private:
        cv::VideoCapture videoCapture;

    public:
        CVFrameStream(int device);
        const SmartPointer<ICameraFrame> getFrame();

    };

}

#endif //SLAM_CVFRAMESTREAM_H
