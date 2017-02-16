//
// Created by Kyler Jensen on 2/15/17.
//

#ifndef SLAM_TELEMETRYPROVIDER_H
#define SLAM_TELEMETRYPROVIDER_H

#include <chrono>
#include "../camera/CameraFrame.hpp"
#include "../pose/Pose.hpp"
#include "TelemetryPacket.hpp"

using namespace slam;

class TelemetryProvider {

private:

    /**
     * @returns The most recently cached camera frame, or <code>nullptr</code>
     * if no camera frames have been recorded.
     * */
    CameraFrame* getCameraFrame();

    /**
     * @returns The timestamp of the most recently cached camera frame,
     * or <code>nullptr</code> if no camera frames have been recorded.
     * */
    Timestamp* getTimestamp();

    /**
     * @returns The most recently cached depth map, or <code>nullptr</code>
     * if no depth maps have been generated.
     * */
    DepthMap* getDepthMap();

    /**
     * @returns The most recently cached pose, or <code>nullptr</code>
     * if no pose has been determined.
     * */
    Pose* getPose();

public:

    void updateWithFrame(CameraFrame& cameraFrame);

    /**
     * Builds a <code>TelemetryPacket</code> from the last recorded camera frame(s).
     * This method makes no guarantee as to the staleness of the returned packet.
     *
     * @returns A complete <code>TelemetryPacket</code>, or <code>nullptr</code> if
     * any required information could not be retrieved (e.g., the camera has not yet
     * recorded any frames or a depth map has not yet been generated)
     * */
    TelemetryPacket* getTelemetryPacket();

};

#endif //SLAM_TELEMETRYPROVIDER_H
