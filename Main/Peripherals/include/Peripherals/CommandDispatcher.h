//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
#include "IHeadlights.h"
#include "PowerManager.h"
#include <istream>
#include <string>
#include <sstream>

class CommandDispatcher {

private:
    ThrustController& thrustController_;
    PowerManager& powerManager_;
    int dispatchCommand(std::stringstream& cmd);
    void goDirection(std::stringstream& cmdString);
    void faceDirection(std::stringstream& cmdString);
    IHeadlights& lights_;
    bool shouldExit_;

public:
    CommandDispatcher(ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights);
    void runLoop(std::istream& in);
    int run(std::stringstream& ss);

};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
