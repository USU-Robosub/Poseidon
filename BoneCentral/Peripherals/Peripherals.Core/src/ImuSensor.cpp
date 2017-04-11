#include "ImuSensor.h"

ImuSensor::ImuSensor(ISensorFactory& sensorFactory, std::shared_ptr<ILogger> logger) :
        accelerometer_(sensorFactory.createAccelerometer()),
        gyroscope_(sensorFactory.createGyroscope()),
        compass_(sensorFactory.createCompass()),
        extPressureSensor_(sensorFactory.createExternalPressureSensor()),
        intPressureSensor_(sensorFactory.createInternalPressureSensor()),
        extTemperatureSensor_(sensorFactory.createExternalTemperatureSensor()),
        intTemperatureSensor1_(sensorFactory.createInternalTemperatureSensor1()),
        intTemperatureSensor2_(sensorFactory.createInternalTemperatureSensor2()),
        logger_(logger)
{
    logger_->info("Initializing sensor...");
}



FloatTuple ImuSensor::getAcceleration()
{
    return accelerometer_->getAcceleration();
}



FloatTuple ImuSensor::getAngularAcceleration() 
{
    return gyroscope_->getAngularAcceleration();
}



FloatTuple ImuSensor::getHeading()
{
    return compass_->getHeading();
}



double ImuSensor::getExtPressure()
{
    return extPressureSensor_->getPressure();
}



double ImuSensor::getIntPressure()
{
    return intPressureSensor_->getPressure();
}



double ImuSensor::getExtTemperature()
{
    return extTemperatureSensor_->getTemperature();
}



double ImuSensor::getIntTemperature()
{
    auto temperatureResults = (intTemperatureSensor1_->getTemperature() + 
            intTemperatureSensor2_->getTemperature()) / 2.0;
    return temperatureResults;
}



void ImuSensor::calibWaterPressure() {
    extPressureSensor_->calibrate();
}



ImuSensor::~ImuSensor()
{
    logger_->info("Closing sensor...");
}