#include "PowerManager.h"

PowerManager::PowerManager()
{
	escsOn = false;
}

void PowerManager::turnOnEscs()
{
	std::ofstream serialOut("/dev/ttyACM0");
	if (!escsOn)
	{
		serialOut << '1' << '1' <<  std::flush;
		escsOn = true;
	}
	serialOut.close();
}

void PowerManager::turnOffEscs()
{
	
	std::ofstream serialOut("/dev/ttyACM0");
	if (escsOn)
	{
		serialOut << '1' << '0' << std::flush;
		escsOn = false;
	}
	serialOut.close();
}
