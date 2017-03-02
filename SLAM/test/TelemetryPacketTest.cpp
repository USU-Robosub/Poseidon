//
// Created by Kyler Jensen on 2/15/17.
//

#include "catch.hpp"
#include "../include/TelemetryPacket.h"

using namespace slam;

TEST_CASE("TelemetryPacket works as expected") {

    auto pose = std::make_shared<Pose>(Pose());
    auto frame = std::make_shared<CameraFrame>(CameraFrame(640, 480));
    auto map = std::make_shared<DepthMap>(DepthMap());
    auto packet = TelemetryPacket();

    packet.cameraFrame = frame;
    packet.depthMap = map;
    packet.pose = pose;


    SECTION("All of TelemetryPacket's members were initialized") {

        REQUIRE(packet.cameraFrame == frame);

        REQUIRE(packet.depthMap == map);

        REQUIRE(packet.pose == pose);

    }

    SECTION("Chrono works as expected") {

        std::chrono::time_point<std::chrono::steady_clock> ts = frame->getTimestamp();

        REQUIRE(ts == frame->getTimestamp());

        REQUIRE(ts == packet.cameraFrame->getTimestamp());

    }

}
