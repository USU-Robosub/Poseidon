#include "ImuPower.h"

ImuPower::ImuPower(std::shared_ptr<MPU6050> accelerometer) : accelerometer_(accelerometer),
		compass_(compass)
{
}

void ImuPower::sleep() {
	accelerometer_->sleep();
	compass_->setMode(Idle);
}

void ImuPower::wake() {
	accelerometer_->awake();
}