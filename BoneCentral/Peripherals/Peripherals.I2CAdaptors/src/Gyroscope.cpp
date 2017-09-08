#include "Gyroscope.h"

Gyroscope::Gyroscope(std::shared_ptr<MPU6050> gyroscope) :
        gyroscope_(gyroscope)
{
}

FloatTuple Gyroscope::getAngularAcceleration()
{
    //return std::make_tuple(gyroscope_->gyro_X(), gyroscope_->gyro_Y(), gyroscope_->gyro_Z());
    return std::make_tuple(0, 0, 0);
}

void Gyroscope::setMagnitude(int)
{
    //MPU6050::FS_SEL selection = static_cast<MPU6050::FS_SEL>(magnitudeOption);
    //gyroscope_->setGyroFullScale(selection);
}
