
#include "IMUSensor.h"
#include <iostream>


//list static members so I can reference them
int IMUSensor::instanceCount_;


IMUSensor::IMUSensor()
{
    if (instanceCount_ >= 1)
        throw new std::runtime_error("Cannot have more than one IMUSensor!");

    std::cout << "Initializing IMUSensor..." << std::endl;

    //create and initialize IMU BMP085 module
    sensorBMP085_ = std::make_shared<BMP085>(0x0); //TODO: need bus ptr
    sensorBMP085_->initialize();
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
