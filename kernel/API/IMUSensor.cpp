
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
    sensorBMP085_->initialize();

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
    sensorBMP085_ = std::make_shared<BMP085>(I2C_SUB2);
}



IMUSensor::~IMUSensor()
{
    std::cout << "Tearing down IMUSensor..." << std::endl;
    instanceCount_--;
}



float IMUSensor::readInteriorTemperature()
{
    return sensorBMP085_->readTemperature();
}



int32_t IMUSensor::readPressure()
{
    return sensorBMP085_->readPressure();
}



int32_t IMUSensor::readSealevelPressure(float altitudeMeters)
{
    return sensorBMP085_->readSealevelPressure(altitudeMeters);
}



float IMUSensor::readAltitude(float sealevelPressure)
{
    return sensorBMP085_->readAltitude(sealevelPressure);
}



Vector3D IMUSensor::readCompass()
{
    return Vector3D(sensorHMC5883L_->X(), sensorHMC5883L_->Y(), sensorHMC5883L_->Z());
}



Vector3D IMUSensor::getAcceleration()
{
    return Vector3D(sensorMPU6050_->accel_X(),
        sensorMPU6050_->accel_Y(), sensorMPU6050_->accel_Z());
}



Vector3D IMUSensor::getGyro()
{
    return Vector3D(sensorMPU6050_->gyro_X(),
        sensorMPU6050_->gyro_Y(), sensorMPU6050_->gyro_Z());
}



int16_t IMUSensor::getTemp()
{
    return sensorMPU6050_->temp();
}


Rice::Array IMUSensor::ruby_Gyro() {
    Rice::Array tmp;
    tmp.push(sensorMPU6050_->gyro_X());
    tmp.push(sensorMPU6050_->gyro_Y());
    tmp.push(sensorMPU6050_->gyro_Z());
    return tmp;
}

Rice::Array IMUSensor::ruby_Acceleration() {
    Rice::Array tmp;
    tmp.push(sensorMPU6050_->accel_X());
    tmp.push(sensorMPU6050_->accel_Y());
    tmp.push(sensorMPU6050_->accel_Z());
    return tmp;
}

Rice::Array IMUSensor::ruby_Compass() {
    Rice::Array tmp;
    tmp.push(sensorHMC5883L_->X());
    tmp.push(sensorHMC5883L_->Y());
    tmp.push(sensorHMC5883L_->Z());
    return tmp;
}
