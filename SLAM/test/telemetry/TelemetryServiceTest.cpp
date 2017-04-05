//
// Created by Kyler Jensen on 4/5/17.
//


#include <catch.hpp>
#include "../../include/telemetry/TelemetryService.h"

using namespace slam;

void doSomething(TelemetryPacket) {

}

TEST_CASE("TelemetryService works as expected") {

    auto telemetryService = TelemetryService();

    REQUIRE(telemetryService.subscribers() == 0);

    SECTION("The user is able to subscribe to and unsubscribe from telemetry updates") {

        auto listener = [](TelemetryPacket) {
            std::cout << "Received telemetry!" << std::endl;
        };

        REQUIRE(telemetryService.subscribers() == 0);

        telemetryService.subscribe(listener);

        REQUIRE(telemetryService.subscribers() == 1);

        telemetryService.subscribe(&doSomething);

        REQUIRE(telemetryService.subscribers() == 2);

        telemetryService.unsubscribe(listener);

        REQUIRE(telemetryService.subscribers() == 1);

        telemetryService.unsubscribe(&doSomething);

        REQUIRE(telemetryService.subscribers() == 0);

    }

}