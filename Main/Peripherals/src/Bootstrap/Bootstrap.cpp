//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <ThrustController.h>
#include <IMUSensor.h>
#include <PowerManagement.h>
#include "RubyLogger.h"
#include "PwmThrusterFactory.h"
#include "ImuFactory.h"
#include "PowerModule/CMPR.h"

int main() {

    auto rubyLogger = std::make_shared<RubyLogger>(&std::cout);

    auto thrusterFactory = PwmThrusterFactory();
    ThrustController(thrusterFactory, rubyLogger);

    auto imuFactory = ImuFactory();
    IMUSensor(imuFactory, rubyLogger);

    auto powerModule = std::make_shared<PowerModule>(I2C_SUB2);
    PowerManagement(powerModule, rubyLogger);

    return 0;
}


