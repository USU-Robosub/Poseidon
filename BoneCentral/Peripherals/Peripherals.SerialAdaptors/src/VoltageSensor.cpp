//
// Created by TekuConcept on 4/8/2017
//

#include "VoltageSensor.h"

VoltageSensor::VoltageSensor(Serial& serial) : serial_(serial) {}

double VoltageSensor::measureVoltage() {
	serial_.writeByte(VOLTAGE_IDX);
	return serial_.readDouble();
}