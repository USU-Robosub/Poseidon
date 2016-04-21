// Headlights.cpp - functions for toggling the headlights on Poseidon
//
// Created by Kevin Burgon on 02/01/2016

#include "../include/Headlights.h"

Headlights::Headlights(Serial& serial) : serial_(serial)
{
	areOn = true; // Initialized as true because Poseidon's headlights are
}				//		are turned on by the arduino in its initialization

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
