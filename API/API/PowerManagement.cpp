
#include "PowerManagement.h"
#include <stdexcept>
#include <iostream>

//list static members so I can reference them
int PowerManagement::instanceCount_;


PowerManagement::PowerManagement():
    bus_(I2C_SUB2)
{
    if (instanceCount_ >= 1)
        throw new std::runtime_error("Cannot have more than one PowerManagement!");

    std::cout << "Initializing PowerManagement..." << std::endl;
}


PowerManagement::~PowerManagement()
{}



void PowerManagement::turnOnESCs()
{
    bus_.write(0x02, 0x02, 0x3F);
}



void PowerManagement::turnOffESCs()
{
    bus_.write(0x02, 0x02, 0x0);
}
