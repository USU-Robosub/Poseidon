//
// Created by Kyler Jensen on 3/29/17.
//

#include "../include/camera_frame/ICameraFrame.h"

using namespace slam;

ICameraFrame::ICameraFrame(const chrono &timestamp) : timestamp(timestamp) {}

const chrono &ICameraFrame::getTimestamp() const {
    return timestamp;
}
