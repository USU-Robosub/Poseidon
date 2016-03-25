#include "ImuSensor.h"

ImuSensor::ImuSensor(IImuFactory& imuFactory, std::shared_ptr<ILogger> logger) :
        accelerometer_(imuFactory.createAccelerometer()),
        gyroscope_(imuFactory.createGyroscope()),
        compass_(imuFactory.createCompass()),
        extPressureSensor_(imuFactory.createExternalPressureSensor()),
        intPressureSensor_(imuFactory.createInternalPressureSensor()),
        extTemperatureSensor_(imuFactory.createExternalTemperatureSensor()),
        intTemperatureSensor1_(imuFactory.createInternalTemperatureSensor1()),
        intTemperatureSensor2_(imuFactory.createInternalTemperatureSensor2()),
        logger_(logger)
{
    logger_->info("Initializing sensor...");
}



FloatTuple ImuSensor::getAcceleration()
{
    return accelerometer_->getAcceleration();
}



FloatTuple getAngularAcceleration() 
{
    return gyroscope_->getAngularAcceleration();
}



FloatTuple ImuSensor::getHeading()
{
    return compass_->getHeading();
}



int ImuSensor::getExtPressure()
{
    return extPressureSensor_->getPressure();
}



int ImuSensor::getIntPressure()
{
    return intPressureSensor_->getPressure();
}



float ImuSensor::getExtTemperature()
{
    return extTemperatureSensor_->getTemperature();
}



float ImuSensor::getIntTemperature()
{
    return (intTemperatureSensor1_->getTemperature() + 
            intTemperatureSensor2_->getTemperature()) / 2.0;
}



ImuSensor::~ImuSensor()
{
    logger_->info("Closing sensor...");
}