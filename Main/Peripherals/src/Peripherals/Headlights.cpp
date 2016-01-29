//
// Headlights.cpp
// Source files for the class Headlights
//
// Created by Kevin Burgon on 01/28/2016
//
#include "Headlights.h"

Headlights::Headlights()
{
	areOn = false;
}

void Headlights::switchLights()
{
	std::ofstream serialOut("/dev/ttyACM0");
	std::ifstream serialIn("/dev/ttyACM0");
	if (areOn)
	{
		serialOut << 0x36 << std::flush;
		serialOut << 0x1 << std::flush;
		areOn == false;
	}
	else
	{
		serialOut << 0x36 << 0x1 << std::flush;
		areOn == true;
	}
	std::string response;
	getline(serialIn, response);
	std::cout << response << std::endl;
	serialIn.close();
	serialOut.close();
}
