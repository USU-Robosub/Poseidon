// Headlights.h - Controls for toggling the headlights of Poseidon
//
// Created by Kevin Burgon on 02/01/2016

#ifndef HEADLIGHTS
#define HEADLIGHTS

#include <iostream>
#include "Serial.h"
#include "IHeadlights.h"

class Headlights : public IHeadlights
{
private:
	bool areOn;
	Serial writeSerial;
public:
	Headlights();
	void switchLights();
};

#endif
