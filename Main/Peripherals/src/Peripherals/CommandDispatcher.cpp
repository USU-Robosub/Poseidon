//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(std::istream& in, ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights, ImuSensor& sensors)
        : in_(in), thrustController_(thrustController), powerManager_(powerManager), lights_(lights), sensors_(sensors), shouldExit_(false) {}

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
    // else if(cmd == "getAcceleration") sensors_.getAcceleration();
    else if(cmd == "getAcceleration") printAcceleration();
    // else if(cmd == "getAngularAcceleration") sensors_.getAngularAcceleration();
    else if(cmd == "getAngularAcceleration") printAngularAcceleration();
    // else if(cmd == "getHeading") sensors_.getHeading();
    else if(cmd == "getHeading") printHeading();
    else if(cmd == "getInternalTemperature") sensors_.getIntTemperature();
    else if(cmd == "getInternalPressure") sensors_.getIntPressure();
    else if(cmd == "setForwardTrim") setForwardTrim(cmdString);
    else if(cmd == "setDiveTrim") setDiveTrim(cmdString);
    else if(cmd == "setDiveOffset") setDiveOffset(cmdString);
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
    std::cout << std::get<0>(acceleration) << ' ' << std::get<1>(acceleration) << ' ' << std::get<2>(acceleration) << std::endl;
}

void CommandDispatcher::printAngularAcceleration() {
    auto angularAcceleration = sensors_.getAngularAcceleration();
    std::cout << std::get<0>(angularAcceleration) << ' ' << std::get<1>(angularAcceleration) << ' ' << std::get<2>(angularAcceleration) << std::endl;
}

void CommandDispatcher::printHeading() {
    auto heading = sensors_.getHeading();
    std::cout << std::get<0>(heading) << ' ' << std::get<1>(heading) << ' ' << std::get<2>(heading) << std::endl;
}

void CommandDispatcher::setForwardTrim(std::stringstream& cmdString) {
    float a, b;
    cmdString >> a >> b;
    thrustController_.setForwardTrim(a, b);
}

void CommandDispatcher::setDiveTrim(std::stringstream& cmdString) {
    float a, b;
    cmdString >> a >> b;
    thrustController_.setDiveTrim(a, b);
}

void CommandDispatcher::setDiveOffset(std::stringstream& cmdString) {
    float a, b;
    cmdString >> a >> b;
    thrustController_.setDiveOffset(a, b);
}
