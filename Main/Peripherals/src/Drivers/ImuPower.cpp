#include "ImuPower.h"

ImuPower::ImuPower(std::shared_ptr<MPU6050> accelerometer) : accelerometer_(accelerometer)
{
}

void ImuPower::sleep() {
	accelerometer_->sleep();
}

void ImuPower::wake() {
	accelerometer_->awake();
}