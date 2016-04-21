#ifndef I2C_FACTORY_H
#define I2C_FACTORY_H

#include <ISensorFactory.h>

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Compass.h"
#include "ExTemperatureSensor.h"
#include "InTemperatureSensor1.h"
#include "InTemperatureSensor2.h"
#include "ExPressureSensor.h"
#include "InPressureSensor.h"
#include "ImuPower.h"

class I2CFactory : public ISensorFactory {
public:
	I2CFactory();
	std::shared_ptr<IAccelerometer> createAccelerometer();
	std::shared_ptr<IGyroscope> createGyroscope();
	std::shared_ptr<ICompass> createCompass();
	std::shared_ptr<ITemperatureSensor> createExternalTemperatureSensor();
	std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor1();
	std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor2();
	std::shared_ptr<IPressureSensor> createExternalPressureSensor();
	std::shared_ptr<IPressureSensor> createInternalPressureSensor();
	std::shared_ptr<IImuPower> createImuPower();

private:
	std::shared_ptr<BMP085> BMP085_sensor_;
	std::shared_ptr<HMC5883L> HMC5883L_sensor_;
	std::shared_ptr<MPU6050> MPU6050_sensor_;
};


#endif