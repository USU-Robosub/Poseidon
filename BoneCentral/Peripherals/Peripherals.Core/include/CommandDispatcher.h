//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
#include "PowerManager.h"
#include "ImuSensor.h"
#include "IHeadlights.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <tuple>

class CommandDispatcher {

private:
    std::istream& in_;
    ThrustController& thrustController_;
    PowerManager& powerManager_;
    IHeadlights& lights_;
    ImuSensor& sensors_;
    bool shouldExit_;

    void dispatchCommand(std::stringstream& cmd);
    void goDirection(std::stringstream& cmdString);
    void faceDirection(std::stringstream& cmdString);

    void setForwardTrim(std::stringstream& cmdString);
    void setDiveTrim(std::stringstream& cmdString);
    void setDiveOffset(std::stringstream& cmdString);

public:
    CommandDispatcher(std::istream& in, ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights, ImuSensor& sensors);
    void runLoop();

};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
