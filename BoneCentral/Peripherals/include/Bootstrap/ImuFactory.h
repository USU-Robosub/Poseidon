#ifndef IMU_FACTORY_H
#define IMU_FACTORY_H

#include <IImuFactory.h>

#include "BMP085.h"
#include "HMC5883L.h"
#include "MPU6050.h"

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Compass.h"
#include "ExTemperatureSensor.h"
#include "InTemperatureSensor1.h"
#include "InTemperatureSensor2.h"
#include "ExPressureSensor.h"
#include "InPressureSensor.h"

class ImuFactory : public IImuFactory {
public:
	ImuFactory(
		std::shared_ptr<BMP085> BMP085_sensor, 
		std::shared_ptr<HMC5883L> HMC5883L_sensor,
		std::shared_ptr<MPU6050> MPU6050_sensor);
	std::shared_ptr<IAccelerometer> createAccelerometer();
	std::shared_ptr<IGyroscope> createGyroscope();
	std::shared_ptr<ICompass> createCompass();
	std::shared_ptr<ITemperatureSensor> createExternalTemperatureSensor();
	std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor1();
	std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor2();
	std::shared_ptr<IPressureSensor> createExternalPressureSensor();
	std::shared_ptr<IPressureSensor> createInternalPressureSensor();

private:
	std::shared_ptr<BMP085> BMP085_sensor_;
	std::shared_ptr<HMC5883L> HMC5883L_sensor_;
	std::shared_ptr<MPU6050> MPU6050_sensor_;
};


#endif