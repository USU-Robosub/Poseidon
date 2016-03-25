#include "InTemperatureSensor1.h"

TemperatureSensor::TemperatureSensor(std::shared_ptr<MPU6050> temperatureSensor) :
        temperatureSensor_(temperatureSensor) {}

float TemperatureSensor::getTemperature()
{
    return temperatureSensor_->temperature();
}