//
// Created by Kyler Jensen on 2/28/17.
//

#ifndef SLAM_IFRAMESTREAM_H
#define SLAM_IFRAMESTREAM_H

#include "../camera_frame/TCameraFrame.h"
#include "../camera_frame/GrayscaleCameraFrame.h"

namespace slam {

    class IFrameStream {

    public:
        const ICameraFrame getFrame() {
            //TODO Implement this
            throw std::runtime_error("Not implemented.");
        };

    };

}

#endif //SLAM_IFRAMESTREAM_H
