#include "ImuSensor.h"

ImuSensor::ImuSensor(IImuFactory& imuFactory, std::shared_ptr<ILogger> logger) :
        accelerometer_(imuFactory.createAccelerometer()),
        compass_(imuFactory.createCompass()),
        pressureSensor_(imuFactory.createPressureSensor()),
        logger_(logger)
{
    logger_->info("Initializing sensor...")
}

FloatTuple ImuSensor::getAcceleration()
{
    return accelerometer_->getAcceleration();
}

FloatTuple ImuSensor::getHeading()
{
    return compass_->getHeading();
}

int ImuSensor::getPressure()
{
    return pressureSensor_->getPressure();
}

/*float ImuSensor::getTemperature()
{
    return temperatureSensor_->getTemperature();
}*/

ImuSensor::~ImuSensor()
{
    logger_->info("Closing sensor...")
}
