//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"
using json = nlohmann::json;

CommandDispatcher::CommandDispatcher(std::istream& in, std::ostream& out, ImuSensor& imuSensor, ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights)
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
    if(cmd == "goDirection") goDirection(cmdString);
    else if(cmd == "faceDirection") faceDirection(cmdString);
    else if(cmd == "thrustForward") thrustForward(cmdString);
    else if(cmd == "faceDirection") dive(cmdString);
    else if(cmd == "turnOnEscs") powerManager_.turnOnEscs();
    else if(cmd == "turnOffEscs") powerManager_.turnOffEscs();
    else if(cmd == "switchLights") lights_.switchLights();
    else if(cmd == "turnOnImu") powerManager_.turnOnImuSensor();
    else if(cmd == "turnOffImu") powerManager_.turnOffImuSensor();
    else if(cmd == "setForwardTrim") setForwardTrim(cmdString);
    else if(cmd == "setStrafeTrim") setStrafeTrim(cmdString);
    else if(cmd == "setDiveTrim") setDiveTrim(cmdString);
    else if(cmd == "setDiveOffset") setDiveOffset(cmdString);
    else if(cmd == "getAcceleration") _getAcceleration();
    else if(cmd == "getAngularAcceleration") _getAngularAcceleration();
    else if(cmd == "getHeading") _getHeading();
    else if(cmd == "getInternalTemperature") _getInternalTemperature();
    else if(cmd == "getInternalPressure") _getInternalPressure();
    else if(cmd == "getExternalTemperature") _getExternalTemperature();
    else if(cmd == "getExternalPressure") _getExternalPressure();
    else if(cmd == "exit") shouldExit_ = true;
}

void CommandDispatcher::goDirection(std::stringstream& cmdString) {
    float forward, strafe, dive;
    cmdString >> forward >> strafe >> dive;
    thrustController_.goDirection(forward, strafe, dive);
}

void CommandDispatcher::faceDirection(std::stringstream& cmdString) {
    float yaw, dive;
    cmdString >> yaw >> dive;
    thrustController_.faceDirection(yaw, dive);
}

void CommandDispatcher::thrustForward(std::stringstream &cmdString) {
    float left, right;
    cmdString >> left >> right;
    thrustController_.thrustForward(left, right);
}

void CommandDispatcher::dive(std::stringstream &cmdString) {
    float front, rear;
    cmdString >> front >> rear;
    thrustController_.dive(front, rear);
}

void CommandDispatcher::setForwardTrim(std::stringstream& cmdString) {
    float a, b;
    cmdString >> a >> b;
    thrustController_.setForwardTrim(a, b);
}

void CommandDispatcher::setStrafeTrim(std::stringstream& cmdString) {
    float a, b;
    cmdString >> a >> b;
    thrustController_.setStrafeTrim(a, b);
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

void CommandDispatcher::_getAcceleration() {
    auto data = imuSensor_.getAcceleration();
    auto accelJson = json{
            {"Type", "Acceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
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
    out_ << accelJson << std::endl;
}

void CommandDispatcher::_getHeading() {
    auto data = imuSensor_.getHeading();
    auto headingJson = json{
            {"Type", "Heading"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)}//,
            //{"Z", std::get<2>(data)}
    };
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
