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
#include <tuple>

class CommandDispatcher {

private:
    std::istream& in_;
    ThrustController& thrustController_;
    PowerManager& powerManager_;
    void dispatchCommand(std::stringstream& cmd);
    void goDirection(std::stringstream& cmdString);
    void faceDirection(std::stringstream& cmdString);
    void printAcceleration();
    void printAngularAcceleration();
    void printHeading();
    IHeadlights& lights_;
    ImuSensor& sensors_;
    bool shouldExit_;

public:
    CommandDispatcher(std::istream& in, ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights, ImuSensor& sensors);
    void runLoop();

};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
