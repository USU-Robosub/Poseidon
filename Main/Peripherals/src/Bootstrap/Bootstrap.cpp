//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <cstring>
#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "ScriptLogger.h"

int main() {

    auto scriptLogger = std::make_shared<ScriptLogger>(&std::cout);
    auto serial = Serial();

    auto thrusterFactory = SerialThrusterFactory(serial);
    ThrustController tc(thrusterFactory, scriptLogger);

    auto pm = PowerManager();

    CommandDispatcher cd(std::cin, tc, pm);
    cd.runLoop();

    return 0;

}


