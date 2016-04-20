#include "I2CFactory.h"

I2CFactory::I2CFactory() :
	BMP085_sensor_(std::make_shared<BMP085>()),
	HMC5883L_sensor_(std::make_shared<HMC5883L>()),
	MPU6050_sensor_(std::make_shared<MPU6050>()) {}



std::shared_ptr<IAccelerometer> I2CFactory::createAccelerometer() {
	return std::make_shared<Accelerometer>(MPU6050_sensor_);
}



std::shared_ptr<IGyroscope> I2CFactory::createGyroscope() {
	return std::make_shared<Gyroscope>(MPU6050_sensor_);
}



std::shared_ptr<ICompass> I2CFactory::createCompass() {
	return std::make_shared<Compass>(HMC5883L_sensor_);
}



std::shared_ptr<ITemperatureSensor> I2CFactory::createExternalTemperatureSensor() {
	return std::make_shared<ExTemperatureSensor>();
}



std::shared_ptr<ITemperatureSensor> I2CFactory::createInternalTemperatureSensor1() {
	return std::make_shared<InTemperatureSensor1>(MPU6050_sensor_);
}



std::shared_ptr<ITemperatureSensor> I2CFactory::createInternalTemperatureSensor2() {
	return std::make_shared<InTemperatureSensor2>(BMP085_sensor_);
}



std::shared_ptr<IPressureSensor> I2CFactory::createExternalPressureSensor() {
	return std::make_shared<ExPressureSensor>();
}



std::shared_ptr<IPressureSensor> I2CFactory::createInternalPressureSensor() {
	return std::make_shared<InPressureSensor>(BMP085_sensor_);
}

std::shared_ptr<IImuPower> I2CFactory::createImuPower() {
	return std::make_shared<ImuPower>(MPU6050_sensor_, HMC5883L_sensor_, BMP085_sensor_);
}