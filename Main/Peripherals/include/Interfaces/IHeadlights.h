// IHeadlights.h - Interface for toggling the headlights of Poseidon
//
// Created by Kevin Burgon on 02/03/2016

#ifndef HEADLIGHTS
#define HEADLIGHTS

#include <iostream>
#include "Serial.h"

class IHeadlights
{
public:
	Headlights() = 0;
	void switchLights() = 0;
};

#endif
