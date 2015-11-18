//
// Created by Nathan Copier on 11/10/2015.
//

#include <ThrustController.h>
#include <iostream>
#include "CommandDispatcher.h"

int main() {
    auto thrustController = ThrustController();
    auto dispatcher = CommandDispatcher(std::cin, thrustController);

    return 0;
}

