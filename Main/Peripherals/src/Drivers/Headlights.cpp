// Headlights.cpp - functions for toggling the headlights on Poseidon
//
// Created by Kevin Burgon on 02/01/2016

#include "Headlights.h"

Headlights::Headlights(Serial& serial) : serial_(serial)
{
	areOn = false;
}

void Headlights::switchLights()
{
	if (areOn)
	{

		serial_.writeByte(0x9);
		serial_.writeByte(0x0);
		areOn = false;
	}
	else
	{
		serial_.writeByte(0x9);
		serial_.writeByte(0x1);
		areOn = true;
	}
}
