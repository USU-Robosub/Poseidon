#include "EscPower.h"

EscPower::EscPower(Serial& serial) : serial_(serial) {}

void EscPower::turnOnEscs()
{
        serial_.writeShort(0x0601);
}

void EscPower::turnOffEscs()
{
        serial_.writeShort(0x0600);
}
