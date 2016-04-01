#include "PowerManager.h"

PowerManager::PowerManager(EscPower& escPower) : escPower_(escPower)
{
	escsOn = false;
}

void PowerManager::turnOnEscs()
{
    escPower_.turnOnEscs();
}

void PowerManager::turnOffEscs()
{
	escPower_.turnOffEscs();
}
