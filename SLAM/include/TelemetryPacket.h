//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_TELEMETRYPACKET_H
#define SLAM_TELEMETRYPACKET_H

#include "CameraFrame.h"
#include "DepthMap.h"
#include "Pose.h"

namespace slam {

    struct TelemetryPacket {

        std::shared_ptr<CameraFrame> cameraFrame;
        std::shared_ptr<DepthMap> depthMap;
        std::shared_ptr<Pose> pose;

    };

}



#endif //SLAM_TELEMETRYPACKET_H
