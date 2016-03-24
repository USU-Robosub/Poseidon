#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(std::shared_ptr<BMP085> temperatureSensor) :
        temperatureSensor_(temperatureSensor) {}

float TemperatureSensor::getTemperature()
{
    return temperatureSensor_->readTemperature();
}
