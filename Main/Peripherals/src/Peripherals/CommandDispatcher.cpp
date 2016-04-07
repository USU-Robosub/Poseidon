//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(std::istream& in, ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights)
        : in_(in), thrustController_(thrustController), powerManager_(powerManager), lights_(lights), shouldExit_(false), sensors_(sensors) {}

void CommandDispatcher::runLoop() {
    while(!shouldExit_) {
        std::string cmd;
        std::getline(in_, cmd);
        std::stringstream ss(cmd);
        dispatchCommand(ss);
    }
}

void CommandDispatcher::dispatchCommand(std::stringstream& cmdString) {
    std::string cmd;
    cmdString >> cmd;
    if(cmd == "goDirection") goDirection(cmdString);
    else if(cmd == "faceDirection") faceDirection(cmdString);
    else if(cmd == "turnOnEscs") powerManager_.turnOnEscs();
    else if(cmd == "turnOffEscs") powerManager_.turnOffEscs();
    else if(cmd == "switchLights") lights_.switchLights();
    else if(cmd == "turnOnImu") powerManager_.turnOnImuSensor();
    else if(cmd == "turnOffImu") powerManager_.turnOffImuSensor();
    else if(cmd == "getAcceleration") printAcceleration();
    else if(cmd == "getAngularAcceleration") printAngularAcceleration();
    else if(cmd == "getHeading") printHeading();
    else if(cmd == "getInternalTemperature") std::cout << sensors_.getIntTemperature() << std::endl;
    else if(cmd == "getInternalPressure") std::cout << sensors_.getIntPressure() << std::endl;
    else if(cmd == "exit") shouldExit_ = true;
}

void CommandDispatcher::goDirection(std::stringstream& cmdString) {
    float forward, strafe, dive;
    cmdString >> forward;
    cmdString >> strafe;
    cmdString >> dive;
    thrustController_.goDirection(forward, strafe, dive);
}

void CommandDispatcher::faceDirection(std::stringstream& cmdString) {
    float yaw;
    cmdString >> yaw;
    thrustController_.faceDirection(yaw);
}

void CommandDispatcher::printAcceleration() {
    auto acceleration = sensors_.getAcceleration();
    std::cout << std::get<0> << ' '
        << std::get<1> << ' '
        << std::Get<2> << std::endl;
}

void CommandDispatcher::printAngularAcceleration() {
    auto angularAcceleration = sensors_.getAngularAcceleration();
    std::cout << std::Get<0> << ' '
        << std::get<1> << ' '
        << std::get<2> << std::endl;
}

void CommandDispatcher::printHeading() {
    auto heading = sensors_.getHeading();
    std::cout << std::Get<0> << ' '
        << std::get<1> << ' '
        << std::get<2> << std::endl;
}