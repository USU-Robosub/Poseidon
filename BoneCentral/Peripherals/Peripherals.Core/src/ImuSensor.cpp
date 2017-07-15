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



FloatTuple ImuSensor::getAcceleration() const
{
    std::lock_guard lock(imuMutex_);
    return accelerometer_->getAcceleration();
}



FloatTuple ImuSensor::getAngularAcceleration() const
{
    std::lock_guard lock(imuMutex_);
    return gyroscope_->getAngularAcceleration();
}



Vector ImuSensor::getHeading() const
{
    std::lock_guard lock(imuMutex_);
    return normalize( compass_->getHeading() );
}

/**
 * Transforms the vector based on the Compass' orientation on the sub
 * also inverts so the return value is the sub's orientation relative to
 * magnetic north rather than north's orientation relative to the sub.
 * @param rawVector
 * @return
 */
Vector ImuSensor::normalize(const Vector& rawVector) const {
    return Vector( rawVector.Z(), -rawVector.X(), -rawVector.Y() );
}


int ImuSensor::getExtPressure() const
{
    std::lock_guard lock(imuMutex_);
    return extPressureSensor_->getPressure();
}



int ImuSensor::getIntPressure() const
{
    std::lock_guard lock(imuMutex_);
    return intPressureSensor_->getPressure();
}



float ImuSensor::getExtTemperature() const
{
    std::lock_guard lock(imuMutex_);
    return extTemperatureSensor_->getTemperature();
}



float ImuSensor::getIntTemperature() const
{
    std::lock_guard lock(imuMutex_);
    auto temperatureResults = (intTemperatureSensor1_->getTemperature() + 
            intTemperatureSensor2_->getTemperature()) / 2.0;
    return (float)temperatureResults;
}



ImuSensor::~ImuSensor()
{
    logger_->info("Closing sensor...");
}