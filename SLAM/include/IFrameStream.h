//
// Created by Kyler Jensen on 2/28/17.
//

#ifndef SLAM_IFRAMESTREAM_H
#define SLAM_IFRAMESTREAM_H

#include "CameraFrame.h"

namespace slam {

    class IFrameStream {

    public:
        virtual std::shared_ptr<CameraFrame> getNextFrame() = 0;

    };

}

#endif //SLAM_IFRAMESTREAM_H
