#include "ImuPower.h"

ImuPower::ImuPower(std::shared_ptr<MPU6050> accelerometer, std::shared_ptr<HMC5883L> compass) : accelerometer_(accelerometer),
		compass_(compass)
{
}

void ImuPower::sleep() {
	accelerometer_->sleep();
	compass_->setMode(HMC5883L::Mode::Idle);
}

void ImuPower::wake() {
	accelerometer_->awake();
}