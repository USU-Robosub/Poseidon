//
// Headlights.h
// Class declaration for Headlights, to be used for toggling the headlights
// on Poseidon
//
// Created by Kevin Burgon on 01/28/2016
//
#ifndef HEADLIGHTS
#define HEADLIGHTS

#include <iostream>
#include <fstream>

class Headlights
{
private:
	bool areOn;
public:
	Headlights();
	void switchLights();
};

#endif
