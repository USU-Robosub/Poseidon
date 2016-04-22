//
// Created by Nathan Copier on 11/17/2015.
//
#include "gtest/gtest.h"
#include <iostream>
#include <memory>
#include <utility>
#include <ImuSensor.h>
#include "MockImuFactory.h"
#include <scriptLogger.h>

void testImuSensor();

int main(void) {
    return 0;
}

void testImuSensor()
{
    auto scriptLogger = std::make_shared<scriptLogger>(&std::cout);

    auto imuFactory = MockImuFactory();
    ImuSensor is(imuFactory, scriptLogger);

}
