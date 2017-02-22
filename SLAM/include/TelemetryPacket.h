//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_TELEMETRYPACKET_H
#define SLAM_TELEMETRYPACKET_H

#include "CameraFrame.h"
#include "DepthMap.h"
#include "Pose.h"

struct TelemetryPacket {

    CameraFrame &cameraFrame;
    DepthMap &depthMap;
    Pose &pose;

    TelemetryPacket(CameraFrame& cf, DepthMap& dm, Pose& p) : cameraFrame(cf), depthMap(dm), pose(p) {}

};

#endif //SLAM_TELEMETRYPACKET_H
