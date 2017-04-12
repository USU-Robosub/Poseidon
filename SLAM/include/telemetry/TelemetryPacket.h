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

        SmartPointer<ICameraFrame> cameraFrame;
        DepthMap depthMap;
        Pose pose;

    };

}



#endif //SLAM_TELEMETRYPACKET_H
