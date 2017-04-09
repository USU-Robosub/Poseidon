//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
#include "PowerManager.h"
#include "IHeadlights.h"
#include "IVoltage.h"
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
    IVoltage& voltmeter_;
    bool shouldExit_;

    void dispatchCommand(std::stringstream& cmd);
    
    void goDirection(std::stringstream& cmdString);
    void rotate(std::stringstream& cmdString);
    void move(std::stringstream& cmdString);
    void strafe(std::stringstream& cmdString);
    void dive(std::stringstream& cmdString);
    void yaw(std::stringstream& cmdString);
    void pitch(std::stringstream& cmdString);
    void roll(std::stringstream& cmdString);
    void kill();

    void _getAcceleration();
    void _getAngularAcceleration();
    void _getHeading();
    void _getInternalTemperature();
    void _getInternalPressure();
    void _getExternalTemperature();
    void _getExternalPressure();
    void _getVoltage();

public:
    CommandDispatcher(std::istream& in, std::ostream& out,
        ImuSensor& imuSensor, ThrustController& thrustController,
        PowerManager& powerManager, IHeadlights& lights,
        IVoltage& voltage);
    void runLoop();

};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
