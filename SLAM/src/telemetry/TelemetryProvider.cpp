//
// Created by Kyler Jensen on 2/15/17.
//


#include "TelemetryProvider.h"

CameraFrame* TelemetryProvider::getCameraFrame() {
    //TODO
    return nullptr;
};

DepthMap* TelemetryProvider::getDepthMap() {
    //TODO
    return nullptr;
};

Timestamp* TelemetryProvider::getTimestamp() {
    //TODO
    return nullptr;
};

Pose* TelemetryProvider::getPose() {
    //TODO
    return nullptr;
};

void TelemetryProvider::updateWithFrame(CameraFrame &cameraFrame) {
    //TODO
}

TelemetryPacket* TelemetryProvider::getTelemetryPacket() {
    auto cameraFrame = getCameraFrame();
    auto timestamp = getTimestamp();
    auto depthMap = getDepthMap();
    auto pose = getPose();

    if (cameraFrame == nullptr) return nullptr;
    if (timestamp == nullptr) return nullptr;
    if (depthMap == nullptr) return nullptr;
    if (pose == nullptr) return nullptr;

    return new TelemetryPacket(*cameraFrame, *timestamp, *depthMap, *pose);
}


