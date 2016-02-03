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
	std::ifstream serialIn("/dev/ttyACM0");
	std::ofstream serialOut("/dev/ttyACM0");
	if (areOn)
	{
		serialOut << 0x36 << std::flush;
		serialOut << 0x1 << std::flush;
		areOn = false;
	}
	else
	{
		serialOut << 0x36 << 0x1 << std::flush;
		areOn = true;
	}
	std::string response;
	getline(serialIn, response);
	serialIn.clear();
	std::cout << response << std::endl;
	serialOut.close();
	serialIn.close();
}

