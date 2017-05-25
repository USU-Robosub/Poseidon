#include "EscPower.h"

EscPower::EscPower(Serial& serial) : serial_(serial) {}

void EscPower::turnOnEscs()
{
        serial_.writeByte(ESC_IDX);
        serial_.writeByte(ENABLE);
}

void EscPower::turnOffEscs()
{
        serial_.writeByte(ESC_IDX);
        serial_.writeByte(DISABLE);
}
