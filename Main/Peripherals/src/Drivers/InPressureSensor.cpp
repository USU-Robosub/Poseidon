#include "InPressureSensor.h"

InPressureSensor::InPressureSensor(std::shared_ptr<BMP085> pressure) :
	pressure_(pressure) {}

int ExPressureSensor::getPressure()
{
    return pressure_->readPressure();
}
