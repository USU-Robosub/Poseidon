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
#include <json.hpp>
#include "ILogger.h"

class CommandDispatcher {

private:
    std::istream& in_;
    std::ostream& out_;
    ImuSensor& imuSensor_;
    ThrustController& thrustController_;
    PowerManager& powerManager_;
    IHeadlights& lights_;
    ILogger& logger_;
    bool shouldExit_;

    void dispatchCommand(std::stringstream& cmd);

    void start();
    void move(std::stringstream& cmdString);
    void dive(std::stringstream& cmdString);
    void yaw(std::stringstream& cmdString);
    void kill();
    void configureYaw(std::stringstream& cmdString);
    void configureTimeDelta(std::stringstream& cmdString);

    void _getAcceleration();
    void _getAngularAcceleration();
    void _getHeading();
    void _getInternalTemperature();
    void _getInternalPressure();
    void _getExternalTemperature();
    void _getExternalPressure();

public:
    CommandDispatcher(
            std::istream& in,
            std::ostream& out,
            ImuSensor& imuSensor,
            ThrustController& thrustController,
            PowerManager& powerManager,
            IHeadlights& lights,
            ILogger& logger
    );
    void runLoop();

};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
