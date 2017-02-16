//
// Created by Kyler Jensen on 2/15/17.
//

#include "../../include/catch.hpp"
#include "../../src/telemetry/TelemetryProvider.h"

TEST_CASE("TelemetryProvider works") {

    auto provider = TelemetryProvider();

    SECTION("getTelemetryPacket() returns nullptr if no frame has been loaded") {
        auto packet = provider.getTelemetryPacket();
        REQUIRE( packet == nullptr );
    }

    SECTION("updateWithFrame() does not throw an error") {
        auto frame = CameraFrame();
        REQUIRE_NOTHROW( provider.updateWithFrame(frame) );
    }

    SECTION("getTelemetryPacket() does NOT return nullptr once a frame has been loaded") {
        auto packet = provider.getTelemetryPacket();
        REQUIRE( packet != nullptr );
    }

}
