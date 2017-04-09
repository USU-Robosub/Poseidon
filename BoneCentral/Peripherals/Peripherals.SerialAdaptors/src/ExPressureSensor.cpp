#include "ExPressureSensor.h"

ExPressureSensor::ExPressureSensor(Serial& serial) : serial_(serial) {}

double ExPressureSensor::getPressure() {
    serial_.writeByte(PRESS_IDX);
	return serial_.readDouble();
}
