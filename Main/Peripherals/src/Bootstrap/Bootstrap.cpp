//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <cstring>
#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "ScriptLogger.h"
#include "EscPower.h"
#include <Headlights.h>

int main() {

    auto scriptLogger = std::make_shared<ScriptLogger>(&std::cout);
    auto serial = Serial();
    auto thrusterFactory = SerialThrusterFactory(serial);
    ThrustController tc(thrusterFactory, scriptLogger);

    
    auto ep = EscPower(serial);
    auto pm = PowerManager(ep);
    auto lights = Headlights(serial);

    CommandDispatcher cd(std::cin, tc, pm, lights);
    cd.runLoop();

    return 0;

}
