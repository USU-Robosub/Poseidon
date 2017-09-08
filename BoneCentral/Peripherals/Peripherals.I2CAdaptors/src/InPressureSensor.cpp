#include "InPressureSensor.h"

InPressureSensor::InPressureSensor(std::shared_ptr<BMP085> pressure) :
	pressure_(pressure) {}

int InPressureSensor::getPressure()
{
    //return pressure_->readPressure();
    return 0;
}
