
#include "IMUSensor.h"

#include <iostream>


//list static members so I can reference them
int IMUSensor::instanceCount_;


IMUSensor::IMUSensor()
{
    if (instanceCount_ >= 1)
        throw new std::runtime_error("Cannot have more than one IMUSensor!");

    std::cout << "Initializing IMUSensor..." << std::endl;

    //create and initialize IMU BMP085 (pressure/temp) module
    std::cout << "Setting up BMP085 chip..." << std::endl;
    sensorBMP085_ = std::make_shared<BMP085>(I2C_SUB2);
    sensorBMP085_->initialize(1);

    //create and initialize IMU HMC5883L (compass) module
    std::cout << "Setting up HMC5883L chip..." << std::endl;
    sensorHMC5883L_ = std::make_shared<HMC5883L>(I2C_SUB2);
    sensorHMC5883L_->setSampleAverage(HMC5883L::Sample::Sx4);
    sensorHMC5883L_->setOutputRate(HMC5883L::Rate::Hz75);
    //sensorHMC5883L_->setGain(HMC5883L::Gain::G8_1);
    sensorHMC5883L_->setMode(HMC5883L::Mode::Single);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //create and initialize IMU MPU6050 (gyro) module
    std::cout << "Setting up MPU6050 chip..." << std::endl;
    sensorMPU6050_ = std::make_shared<MPU6050>(I2C_SUB2);
}



IMUSensor::~IMUSensor()
{
    std::cout << "Tearing down IMUSensor..." << std::endl;
    instanceCount_--;
}



float IMUSensor::readTemperature()
{
    return sensorBMP085_->readTemperature();
}



int32_t IMUSensor::readPressure()
{
    return sensorBMP085_->readPressure();
}



int32_t IMUSensor::readSealevel(float altitudeMeters)
{
    return sensorBMP085_->readSealevelPressure(altitudeMeters);
}



float IMUSensor::readAltitude(float sealevelPressure)
{
    return sensorBMP085_->readAltitude(sealevelPressure);
}



Rice::Object IMUSensor::readCompass()
{
	Rice::String x("X");
	Rice::String y("Y");
	Rice::String z("Z");
	Rice::Hash h;
	h[x] = static_cast<int32_t>(sensorHMC5883L_->X());
	h[y] = static_cast<int32_t>(sensorHMC5883L_->Y());
	h[z] = static_cast<int32_t>(sensorHMC5883L_->Z());
	return h;
}



int32_t IMUSensor::readCompassX()
{
	return static_cast<int32_t>(sensorHMC5883L_->X());
}



int32_t IMUSensor::readCompassY()
{
	return static_cast<int32_t>(sensorHMC5883L_->Y());
}



int32_t IMUSensor::readCompassZ()
{
	return static_cast<int32_t>(sensorHMC5883L_->Z());
}



Rice::Object IMUSensor::readAccelerometer()
{
	Rice::String x("X");
	Rice::String y("Y");
	Rice::String z("Z");
	Rice::Hash h;
	h[x] = static_cast<int32_t>(sensorMPU6050_->accel_X());
	h[y] = static_cast<int32_t>(sensorMPU6050_->accel_Y());
	h[z] = static_cast<int32_t>(sensorMPU6050_->accel_Z());
	return h;
}



int32_t IMUSensor::readAccelX()
{
	return static_cast<int32_t>(sensorMPU6050_->accel_X());
}



int32_t IMUSensor::readAccelY()
{
	return static_cast<int32_t>(sensorMPU6050_->accel_Y());
}



int32_t IMUSensor::readAccelZ()
{
	return static_cast<int32_t>(sensorMPU6050_->accel_Z());
}



Rice::Object IMUSensor::readGyroscope()
{
	Rice::String x("X");
	Rice::String y("Y");
	Rice::String z("Z");
	Rice::Hash h;
	h[x] = static_cast<int32_t>(sensorMPU6050_->gyro_X());
	h[y] = static_cast<int32_t>(sensorMPU6050_->gyro_Y());
	h[z] = static_cast<int32_t>(sensorMPU6050_->gyro_Z());
	return h;
}



int32_t IMUSensor::readGyroX()
{
	return static_cast<int32_t>(sensorMPU6050_->gyro_X());
}



int32_t IMUSensor::readGyroY()
{
	return static_cast<int32_t>(sensorMPU6050_->gyro_Y());
}



int32_t IMUSensor::readGyroZ()
{
	return static_cast<int32_t>(sensorMPU6050_->gyro_Z());
}



float IMUSensor::getTemp()
{
    return sensorMPU6050_->temp();
}



void IMUSensor::turnOn() {
    sensorMPU6050_->awake();
}



void IMUSensor::turnOff() {
    sensorMPU6050_->sleep();
}
