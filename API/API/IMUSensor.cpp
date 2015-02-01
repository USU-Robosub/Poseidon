
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
    sensorBMP085_ = std::make_shared<BMP085>(IMU_ENVIRONMENT_ADDR);
    sensorBMP085_->initialize();

    //create and initialize IMU HMC5883L (compass) module
    std::cout << "Setting up HMC5883L chip..." << std::endl;
    sensorHMC5883L_ = std::make_shared<HMC5883L>(IMU_COMPASS_ADDR);
    sensorHMC5883L_->setSampleAverage(HMC5883L::Sample::Sx4);
    sensorHMC5883L_->setOutputRate(HMC5883L::Rate::Hz75);
    //sensorHMC5883L_->setGain(HMC5883L::Gain::G8_1);
    sensorHMC5883L_->setMode(HMC5883L::Mode::Single);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
