#include "ExTemperatureSensor.h"

ExTemperatureSensor::ExTemperatureSensor(Serial& serial) : serial_(serial) {}

double ExTemperatureSensor::getTemperature() {
    serial_.writeByte(TEMPR_IDX);
	return serial_.readDouble();
}
