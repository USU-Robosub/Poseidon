#ifndef IMU_POWER_H
#define IMU_POWER_H

#include <MPU6050.h>
#include <IImuPower.h>

class ImuPower : IImuPower
{
private:
	std::shared_ptr<MPU6050> accelerometer_;
public:
	ImuPower(std::shared_ptr<MPU6050> accelerometer);
	void sleep();
	void wake();
};

#endif