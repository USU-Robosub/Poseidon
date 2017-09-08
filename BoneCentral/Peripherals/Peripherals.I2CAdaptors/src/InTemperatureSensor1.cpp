#include "InTemperatureSensor1.h"

InTemperatureSensor1::InTemperatureSensor1(std::shared_ptr<MPU6050> temperatureSensor) :
        temperatureSensor_(temperatureSensor) {}

float InTemperatureSensor1::getTemperature()
{
    //return temperatureSensor_->temperature();
    return 0;
}
