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



int ImuSensor::getExtPressure()
{
    auto pressureResults = extPressureSensor_->getPressure();
    std::stringstream logResults;
    logResults << "External Pressure: " << pressureResults;
    std::string toLog = logResults.str();
    logger_->info(toLog.c_str());
    return pressureResults;
}



int ImuSensor::getIntPressure()
{
    auto pressureResults = intPressureSensor_->getPressure();
    std::stringstream logResults;
    logResults << "Internal Pressure: " << pressureResults;
    std::string toLog = logResults.str();
    logger_->info(toLog.c_str());
    return pressureResults;
}



float ImuSensor::getExtTemperature()
{
    auto temperatureResults = extTemperatureSensor_->getTemperature();
    std::stringstream logResults;
    logResults << "External Temperature: " << temperatureResults;
    std::string toLog = logResults.str();
    logger_->info(toLog.c_str());
    return temperatureResults;
}



float ImuSensor::getIntTemperature()
{
    auto temperatureResults = (intTemperatureSensor1_->getTemperature() + 
            intTemperatureSensor2_->getTemperature()) / 2.0;
    std::stringstream logResults;
    logResults << "Internal Temperature: " << temperatureResults;
    std::string toLog = logResults.str();
    logger_->info(toLog.c_str());
    return temperatureResults;
}



ImuSensor::~ImuSensor()
{
    logger_->info("Closing sensor...");
}