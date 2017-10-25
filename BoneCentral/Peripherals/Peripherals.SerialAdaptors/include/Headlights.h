// Headlights.h - Controls for toggling the headlights of Poseidon
//
// Created by Kevin Burgon on 02/01/2016

#ifndef HEADLIGHTS
#define HEADLIGHTS

#include <IHeadlights.h>
#include "Serial.h"
#include "ArduinoConfig.h"

class Headlights : public IHeadlights {
private:
	bool areOn;
	Serial& serial_;
public:
	Headlights(Serial& serial);
	void switchLights();
};

#endif
