#include "Accelerometer.h"

Accelerometer::Accelerometer(std::shared_ptr<MPU6050> accelerometer) :
        accelerometer_(accelerometer)
{
}

FloatTuple Accelerometer::getAcceleration()
{
    //return std::make_tuple(accelerometer_->accel_X(), accelerometer_->accel_Y(), accelerometer_->accel_Z());
    return std::make_tuple(0, 0, 0);
}

void Accelerometer::setMagnitude(int)
{

    //MPU6050::AFS_SEL selection = static_cast<MPU6050::AFS_SEL>(magnitudeOption);
    //accelerometer_->setAcclFullScale(selection);
}
