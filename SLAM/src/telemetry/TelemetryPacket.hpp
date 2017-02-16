//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_TELEMETRYPACKET_HPP
#define SLAM_TELEMETRYPACKET_HPP


#include "../camera/CameraFrame.hpp"
#include "../pose/Pose.hpp"
#include "../depth/DepthMap.hpp"

using namespace slam;

struct TelemetryPacket {

    CameraFrame &cameraFrame;
    Timestamp &timestamp;
    DepthMap &depthMap;
    Pose &pose;

    TelemetryPacket(CameraFrame &cameraFrame, Timestamp &timestamp, DepthMap &depthMap, Pose &pose) :
            cameraFrame(cameraFrame),
            timestamp(timestamp),
            depthMap(depthMap),
            pose(pose) {}

};


#endif //SLAM_TELEMETRYPACKET_HPP
