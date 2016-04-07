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
    auto accelerometerResults = accelerometer_->getAcceleration();
    std::stringstream logResults;
    logResults << "A: " << std::get<0>(accelerometerResults) << ' ' << std::get<1>(accelerometerResults) << ' ' << std::get<2>(accelerometerResults);
    logger_->info(logResults.str());
    return accelerometerResults;
}



FloatTuple ImuSensor::getAngularAcceleration() 
{
    auto gyroscopeResults = gyroscope_->getAngularAcceleration();
    std::stringstream logResults;
    logResults << "A: " << std::get<0>(gyroscopeResults) << ' ' << std::get<1>(gyroscopeResults) << ' ' << std::get<2>(gyroscopeResults);
    logger_->info(logResults.str());
    return gyroscopeResults;
}



FloatTuple ImuSensor::getHeading()
{
    auto compassResults = compass_->getHeading();
    std::stringstream logResults;
    logResults << "A: " << std::get<0>(compassResults) << ' ' << std::get<1>(compassResults) << ' ' << std::get<2>(compassResults);
    logger_->info(logResults.str());
    return compassResults;
}



int ImuSensor::getExtPressure()
{
    auto pressureResults = extPressureSensor_->getPressure();
    std::stringstream logResults;
    logResults << "External Pressure: " << pressureResults;
    logger_->info(logResults.str());
    return pressureResults;
}



int ImuSensor::getIntPressure()
{
    auto pressureResults = intPressureSensor_->getPressure();
    std::stringstream logResults;
    logResults << "Internal Pressure: " << pressureResults;
    logger_->info(logResults.str());
    return pressureResults;
}



float ImuSensor::getExtTemperature()
{
    auto temperatureResults = extTemperatureSensor_->getTemperature();
    std::stringstream logResults;
    logResults << "External Temperature: " << temperatureResults;
    logger_->info(logResults.str());
    return temperatureResults;
}



float ImuSensor::getIntTemperature()
{
    auto temperatureResults = (intTemperatureSensor1_->getTemperature() + 
            intTemperatureSensor2_->getTemperature()) / 2.0;
    std::stringstream logResults;
    logResults << "Internal Temperature: " << temperatureResults;
    logger_->info(logResults.str());
    return temperatureResults;
}



ImuSensor::~ImuSensor()
{
    logger_->info("Closing sensor...");
}