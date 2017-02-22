//
// Created by Kyler Jensen on 2/15/17.
//

#include "catch.hpp"
#include "../include/TelemetryPacket.h"

TEST_CASE("TelemetryPacket can be constructed") {

    auto pose = Pose();
    auto frame = CameraFrame();
    auto depthMap = DepthMap();
    auto packet = new TelemetryPacket(frame, depthMap, pose);

    REQUIRE(packet != nullptr);

}
