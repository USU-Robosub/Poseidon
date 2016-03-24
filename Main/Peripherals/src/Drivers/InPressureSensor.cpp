#include "InPressureSensor.h"

InPressureSensor::InPressureSensor(std::shared_ptr<BMP085> pressure) :
	pressure_(pressure) {}

float ExPressureSensor::getPressure()
{
    return pressure_->readPressure();
}
