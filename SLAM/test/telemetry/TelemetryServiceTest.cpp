//
// Created by Kyler Jensen on 4/5/17.
//


#include <catch.hpp>
#include "../../include/telemetry/TelemetryService.h"

using namespace slam;

void doSomething(TelemetryPacket) {

}

TEST_CASE("TelemetryService works as expected") {

    auto telemetry = TelemetryService();

    REQUIRE(telemetry.subscribers() == 0);

    SECTION("The user is able to subscribe to and unsubscribe from telemetry updates") {

        auto listener = [](TelemetryPacket) {
            std::cout << "Received telemetry!" << std::endl;
        };

        REQUIRE(telemetry.subscribers() == 0);

        telemetry.subscribe(listener);

        REQUIRE(telemetry.subscribers() == 1);

        telemetry.subscribe(&doSomething);

        REQUIRE(telemetry.subscribers() == 2);

        telemetry.unsubscribe(listener);

        REQUIRE(telemetry.subscribers() == 1);

        telemetry.unsubscribe(&doSomething);

        REQUIRE(telemetry.subscribers() == 0);

    }

}