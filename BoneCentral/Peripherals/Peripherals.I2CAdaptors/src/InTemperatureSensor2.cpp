#include "../include/InTemperatureSensor2.h"

InTemperatureSensor2::InTemperatureSensor2(std::shared_ptr<BMP085> temperatureSensor) :
        temperatureSensor_(temperatureSensor) {}

float InTemperatureSensor2::getTemperature()
{
    return temperatureSensor_->readTemperature();
}
