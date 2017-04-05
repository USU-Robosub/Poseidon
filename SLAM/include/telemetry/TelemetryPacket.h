//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_TELEMETRYPACKET_H
#define SLAM_TELEMETRYPACKET_H

#include "../camera_frame/TCameraFrame.h"
#include "DepthMap.h"
#include "Pose.h"

namespace slam {

    struct TelemetryPacket {

        const ICameraFrame& cameraFrame;
        const DepthMap& depthMap;
        const Pose& pose;

    };

}



#endif //SLAM_TELEMETRYPACKET_H
