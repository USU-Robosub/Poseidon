// Headlights.cpp - functions for toggling the headlights on Poseidon
//
// Created by Kevin Burgon on 02/01/2016

#include "Headlights.h"

Headlights::Headlights(Serial& serial) : serial_(serial)
{
	areOn = true; // Initialized as true because Poseidon's headlights are
}				//		are turned on by the arduino in its initialization

void Headlights::switchLights()
{
	if (areOn)
	{
        serial_.writeByte(LIGHT_IDX);
        serial_.writeByte(DISABLE);
		areOn = false;
	}
	else
	{
        serial_.writeByte(LIGHT_IDX);
        serial_.writeByte(ENABLE);
		areOn = true;
	}
}
