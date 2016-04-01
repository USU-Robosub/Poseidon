#ifndef IMU_POWER_H
#define IMU_POWER_H

#include "MPU6050.h"
#include "HMC5883L.h"
#include <IImuPower.h>
#include <memory>
#include <utility>

class ImuPower : public IImuPower
{
private:
	std::shared_ptr<MPU6050> accelerometer_;
	std::shared_ptr<HMC5883L> compass_;
public:
	ImuPower(std::shared_ptr<MPU6050> accelerometer, std::shared_ptr<HMC5883L> compass);
	void sleep();
	void wake();
};

#endif