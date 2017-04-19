//
// Created by Kyler Jensen on 2/15/17.
//

#include <catch.hpp>
#include "../../include/telemetry/TelemetryPacket.h"
#include "../../include/camera_frame/GrayscaleCameraFrame.h"

using namespace slam;

TEST_CASE("TelemetryPacket works as expected") {

    auto now = std::chrono::steady_clock::now();
    auto frame = GrayscaleCameraFrame(640, 480, now);
    auto map = DepthMap(0, 0);
    auto pose = Pose();

    TelemetryPacket packet = { frame, map, pose };

    SECTION("All of TelemetryPacket's members were initialized") {

        REQUIRE(packet.cameraFrame.getRows() == 640);
        REQUIRE(packet.cameraFrame.getCols() == 480);
        REQUIRE(packet.cameraFrame.getColorSpace() == GRAYSCALE);
        REQUIRE(packet.cameraFrame.getTimestamp() == now);

    }

    SECTION("Chrono works as expected") {

        std::chrono::time_point<std::chrono::steady_clock> ts = frame.getTimestamp();

        REQUIRE(ts == frame.getTimestamp());

        REQUIRE(ts == packet.cameraFrame.getTimestamp());

    }

}
