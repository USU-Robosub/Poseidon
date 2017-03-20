//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"
using json = nlohmann::json;

CommandDispatcher::CommandDispatcher(std::istream& in, std::ostream& out,
    ImuSensor& imuSensor, ThrustController& thrustController,
    PowerManager& powerManager, IHeadlights& lights)
        : in_(in),
          out_(out),
          imuSensor_(imuSensor),
          thrustController_(thrustController),
          powerManager_(powerManager),
          lights_(lights),
          shouldExit_(false) {}

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
    if(cmd == "goDirection")                    goDirection(cmdString);
    else if(cmd == "rotate")                    rotate(cmdString);
    else if(cmd == "move")                      move(cmdString);
    else if(cmd == "secondaryDive")             strafe(cmdString);
    else if(cmd == "primaryDive")               dive(cmdString);
    else if(cmd == "yaw")                       yaw(cmdString);
    else if(cmd == "pitch")                     pitch(cmdString);
    else if(cmd == "roll")                      roll(cmdString);
    else if(cmd == "killThrust")                kill();
    else if(cmd == "turnOnEscs")                powerManager_.turnOnEscs();
    else if(cmd == "turnOffEscs")               powerManager_.turnOffEscs();
    else if(cmd == "switchLights")              lights_.switchLights();
    else if(cmd == "turnOnImu")                 powerManager_.turnOnImuSensor();
    else if(cmd == "turnOffImu")                powerManager_.turnOffImuSensor();
    else if(cmd == "getAcceleration")           _getAcceleration();
    else if(cmd == "getAngularAcceleration")    _getAngularAcceleration();
    else if(cmd == "getHeading")                _getHeading();
    else if(cmd == "getInternalTemperature")    _getInternalTemperature();
    else if(cmd == "getInternalPressure")       _getInternalPressure();
    else if(cmd == "getExternalTemperature")    _getExternalTemperature();
    else if(cmd == "getExternalPressure")       _getExternalPressure();
    else if(cmd == "exit")                      shouldExit_ = true;
}




void CommandDispatcher::goDirection(std::stringstream& cmdString) {
    float move, strafe, dive;
    cmdString >> move >> strafe >> dive;
#ifdef DEBUG
    std::cout << "Move: " << move;
    std::cout << " Strafe: " << strafe;
    std::cout << " Dive: " << dive << std::endl;
#endif
    thrustController_.goDirection(move, strafe, dive);
}

void CommandDispatcher::rotate(std::stringstream& cmdString) {
    float yaw, pitch, roll;
    cmdString >> yaw >> pitch >> roll;
#ifdef DEBUG
    std::cout << "Yaw: " << yaw;
    std::cout << " Pitch: " << pitch;
    std::cout << " Roll: " << roll << std::endl;
#endif
    thrustController_.rotate(yaw, pitch, roll);
}

void CommandDispatcher::move(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
#ifdef DEBUG
    std::cout << "Move: " << throttle << std::endl;
#endif
    thrustController_.move(throttle);
}

void CommandDispatcher::strafe(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
#ifdef DEBUG
    std::cout << "Strafe: " << throttle << std::endl;
#endif
    thrustController_.strafe(throttle);
}

void CommandDispatcher::dive(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
#ifdef DEBUG
    std::cout << "Dive: " << throttle << std::endl;
#endif
    thrustController_.dive(throttle);
}

void CommandDispatcher::yaw(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
#ifdef DEBUG
    std::cout << "Yaw: " << throttle << std::endl;
#endif
    thrustController_.yaw(throttle);
}

void CommandDispatcher::pitch(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
#ifdef DEBUG
    std::cout << "Pitch: " << throttle << std::endl;
#endif
    thrustController_.pitch(throttle);
}

void CommandDispatcher::roll(std::stringstream &cmdString) {
    float throttle;
    cmdString >> throttle;
#ifdef DEBUG
    std::cout << "Roll: " << throttle << std::endl;
#endif
    thrustController_.roll(throttle);
}

void CommandDispatcher::kill() {
#ifdef DEBUG
    std::cout << "Killed Thrusters" << std::endl;
#endif
    thrustController_.killAllThrusters();
}




void CommandDispatcher::_getAcceleration() {
    auto data = imuSensor_.getAcceleration();
    auto accelJson = json{
            {"Type", "Acceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    #ifdef DEBUG
    std::cerr << accelJson << std::endl;
    #endif
    out_ << accelJson << std::endl;
}

void CommandDispatcher::_getAngularAcceleration() {
    std::cout << "Fetching angular acceleration" << std::endl;
    auto data = imuSensor_.getAngularAcceleration();
    auto accelJson = json{
            {"Type", "AngularAcceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    #ifdef DEBUG
    std::cerr << accelJson << std::endl;
    #endif
    out_ << accelJson << std::endl;
}

void CommandDispatcher::_getHeading() {
    auto data = imuSensor_.getHeading();
    auto headingJson = json{
            {"Type", "Heading"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    #ifdef DEBUG
    std::cerr << headingJson << std::endl;
    #endif
    out_ << headingJson << std::endl;
}

void CommandDispatcher::_getInternalTemperature() {
    auto data = imuSensor_.getIntTemperature();
    out_ << json{{"Type", "InternalTemperature"},{"Value",data}} << std::endl;
}

void CommandDispatcher::_getInternalPressure() {
    auto data = imuSensor_.getIntPressure();
    out_ << json{{"Type", "InternalPressure"},{"Value",data}} << std::endl;
}

void CommandDispatcher::_getExternalTemperature() {
    auto data = imuSensor_.getExtTemperature();
    out_ << json{{"Type", "ExternalTemperature"},{"Value",data}} << std::endl;
}

void CommandDispatcher::_getExternalPressure() {
    auto data = imuSensor_.getExtPressure();
    out_ << json{{"Type", "ExternalPressure"},{"Value",data}} << std::endl;
}
