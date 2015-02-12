#include "PowerManagement.h"
#include <stdexcept>
#include <iostream>

//list static members so I can reference them
int PowerManagement::instanceCount_;


PowerManagement::PowerManagement():
    module(I2C_SUB2)
{
    if (instanceCount_ >= 1)
        throw new std::runtime_error("Cannot have more than one PowerManagement!");

    std::cout << "Initializing PowerManagement..." << std::endl;
}


PowerManagement::~PowerManagement()
{}



void PowerManagement::turnOnESCs()
{
    module.burstEnableESC(0xE7); // B11100111
}



void PowerManagement::turnOffESCs()
{
    module.burstEnableESC(0x00);
}

