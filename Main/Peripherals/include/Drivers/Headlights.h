// Headlights.h - Controls for toggling the headlights of Poseidon
//
// Created by Kevin Burgon on 02/01/2016

#ifndef HEADLIGHTS
#define HEADLIGHTS

#include <IHeadlights.h>
#include "Serial.h"

// class IHeadlights {
// public:
// 	// IHeadlights() = 0;
// 	virtual void switchLights() = 0;
// };

class Headlights : public IHeadlights {
private:
	bool areOn;
	Serial writeSerial;
public:
	Headlights();
	void switchLights();
};

#endif
