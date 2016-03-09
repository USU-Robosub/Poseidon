//
// Created by Nathan Copier on 11/22/2015.
//

#include "MockImuFactory.h"

std::shared_ptr<IPressureSensor> MockImuFactory::createPressureSensor() {
    return std::make_shared<MockPressureSensor>();
}

std::shared_ptr<ICompass> MockImuFactory::createCompass() {
    return std::make_shared<MockCompass>();
}

std::shared_ptr<IAccelerometer> MockImuFactory::createAccelerometer() {
    return std::make_shared<MockAccelerometer>();
}

std::shared_ptr<IGyroscope> MockImuFactory::createGyroscope()
{
    return std::make_shared<MockGyroscope>();
}

std::shared_ptr<ITemperatureSensor> MockImuFactory::createTemperatureSensor()
{
    return std::make_shared<MockTemperatureSensor>();
}
