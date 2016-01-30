//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <cstring>
#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "RubyLogger.h"
#include <Serial.h>
#include <PowerManager.h>

int main() {

    auto rubyLogger = std::make_shared<RubyLogger>(&std::cout);
    auto serial = Serial();

    auto thrusterFactory = SerialThrusterFactory(serial);
    ThrustController tc(thrusterFactory, rubyLogger);

    auto pm = PowerManager();

    CommandDispatcher cd(std::cin, tc, pm);
    cd.runLoop();

    return 0;

}


