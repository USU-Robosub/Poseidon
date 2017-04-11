#include "ExPressureSensor.h"

ExPressureSensor::ExPressureSensor(Serial& serial)
    : serial_(serial), base_(0) {}

double ExPressureSensor::getPressure() {
    serial_.writeByte(PRESS_IDX);
	return (serial_.readDouble() - base_);
}

void ExPressureSensor::calibrate() {
    serial_.writeByte(PRESS_IDX);
    base_ = serial_.readDouble();
}