#include "ImuFactory.h"

ImuFactory::ImuFactory(Serial& serial) :
	BMP085_sensor_(std::make_shared<BMP085>()),
	HMC5883L_sensor_(std::make_shared<HMC5883L>()),
	MPU6050_sensor_(std::make_shared<MPU6050>()),
	serial_(serial) {}



std::shared_ptr<IAccelerometer> ImuFactory::createAccelerometer() {
	return std::make_shared<Accelerometer>(MPU6050_sensor_);
}



std::shared_ptr<IGyroscope> ImuFactory::createGyroscope() {
	return std::make_shared<Gyroscope>(MPU6050_sensor_);
}



std::shared_ptr<ICompass> ImuFactory::createCompass() {
	return std::make_shared<Compass>(HMC5883L_sensor_);
}



std::shared_ptr<ITemperatureSensor> ImuFactory::createExternalTemperatureSensor() {
	return std::make_shared<ExTemperatureSensor>();
}



std::shared_ptr<ITemperatureSensor> ImuFactory::createInternalTemperatureSensor1() {
	return std::make_shared<InTemperatureSensor1>(MPU6050_sensor_);
}



std::shared_ptr<ITemperatureSensor> ImuFactory::createInternalTemperatureSensor2() {
	return std::make_shared<InTemperatureSensor2>(BMP085_sensor_);
}



std::shared_ptr<IPressureSensor> ImuFactory::createExternalPressureSensor() {
	return std::make_shared<ExPressureSensor>();
}



std::shared_ptr<IPressureSensor> ImuFactory::createInternalPressureSensor() {
	return std::make_shared<InPressureSensor>(BMP085_sensor_);
}

std::shared_ptr<IImuPower> ImuFactory::createImuPower() {
	return std::make_shared<ImuPower>(MPU6050_sensor_, HMC5883L_sensor_, BMP085_sensor_);
}
std::shared_ptr<IEscPower> ImuFactory::createEscPower() {
	return std::make_shared<EscPower>(serial_);
}