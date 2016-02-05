// Headlights.cpp - functions for toggling the headlights on Poseidon
//
// Created by Kevin Burgon on 02/01/2016

#include "Headlights.h"

Headlights::Headlights()
{
	areOn = false;
}

void Headlights::switchLights()
{
	if (areOn)
	{

		writeSerial.writeByte(0x36);
		writeSerial.writeByte(0x1);
		areOn = false;
	}
	else
	{
		writeSerial.writeByte(0x36);
		writeSerial.writeByte(0x1);
		areOn = true;
	}
}
