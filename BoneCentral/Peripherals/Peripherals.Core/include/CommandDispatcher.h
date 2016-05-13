//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
#include "PowerManager.h"
#include "IHeadlights.h"
#include "ImuSensor.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <tuple>
#include <json.h>
#include "ILogger.h"

class CommandDispatcher {

private:
    std::istream& in_;
    std::ostream& out_;
    ImuSensor& imuSensor_;
    ThrustController& thrustController_;
    PowerManager& powerManager_;
    IHeadlights& lights_;
    bool shouldExit_;

    void dispatchCommand(std::stringstream& cmd);
    void goDirection(std::stringstream& cmdString);
    void faceDirection(std::stringstream& cmdString);

    void setForwardTrim(std::stringstream& cmdString);
    void setDiveTrim(std::stringstream& cmdString);
    void setDiveOffset(std::stringstream& cmdString);

    void _getAcceleration();
    void _getAngularAcceleration();
    void _getHeading();
    void _getInternalTemperature();
    void _getInternalPressure();
    void _getExternalTemperature();
    void _getExternalPressure();

public:
    CommandDispatcher(std::istream& in, std::ostream& out, ImuSensor& imuSensor, ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights);
    void runLoop();

};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
