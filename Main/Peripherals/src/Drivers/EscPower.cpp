#include "EscPower.h"

EscPower::EscPower(Serial& serial) : serial_(serial)
{
	escsOn = false;
}

void EscPower::turnOnEscs()
{
	if (!escsOn)
	{
        serial_.writeByte(0x6);
        serial_.writeByte(0x1);
		escsOn = true;
	}
}

void EscPower::turnOffEscs()
{
	if (escsOn)
	{
        serial_.writeByte(0x6);
        serial_.writeByte(0x0);
		escsOn = false;
	}
}
