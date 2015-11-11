#include "PowerManagement.h"

PowerManagement::PowerManagement():
    module(I2C_SUB2)
{

    std::cout << "Initializing PowerManagement..." << std::endl;
}


PowerManagement::~PowerManagement()
{}



void PowerManagement::turnOnESCs()
{
    module.burstEnableESC(0xE7);
}



void PowerManagement::turnOffESCs()
{
    module.burstEnableESC(0x00);
}

