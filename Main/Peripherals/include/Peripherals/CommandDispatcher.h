//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
#include <istream>
#include <string>
#include <sstream>

class CommandDispatcher {
private:
    ThrustController& thrustController_;
    void dispatchCommand(std::stringstream cmd);
    void goDirection(std::stringstream cmdString);
    void faceDirection(std::stringstream cmdString);
public:
    CommandDispatcher(std::istream& in, ThrustController& thrustController);
};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
