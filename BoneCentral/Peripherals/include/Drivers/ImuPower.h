#ifndef IMU_POWER_H
#define IMU_POWER_H

#include "MPU6050.h"
#include "HMC5883L.h"
#include "BMP085.h"
#include <IImuPower.h>
#include <memory>
#include <utility>

class ImuPower : public IImuPower
{
private:
	std::shared_ptr<MPU6050> accelerometer_;
	std::shared_ptr<HMC5883L> compass_;
	std::shared_ptr<BMP085> pressure_;
public:
	ImuPower(std::shared_ptr<MPU6050> accelerometer,
		std::shared_ptr<HMC5883L> compass, std::shared_ptr<BMP085> pressure);
	void sleep();
	void wake();
};

#endif