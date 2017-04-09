//
// Created by TekuConcept on 4/8/2017
//

#ifndef VOLTAGE
#define VOLTAGE

#include <IVoltage.h>
#include "Serial.h"
#include "ArduinoConfig.h"

class VoltageSensor : public IVoltage {
private:
	Serial& serial_;
public:
	VoltageSensor(Serial& serial);
	double measureVoltage();
};

#endif