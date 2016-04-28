//
// Created by Nathan Copier on 4/26/2016.
//

#include "ImuDispatcher.h"
using json = nlohmann::json;

ImuDispatcher::ImuDispatcher(ImuSensor& imuSensor, std::istream& in, std::ostream& out) :
        imuSensor_(imuSensor),
        in_(in),
        out_(out),
        shouldExit_(false) {}

void ImuDispatcher::startListening() {
    thread_ = std::thread([&](){_runLoop();});
}

void ImuDispatcher::_runLoop() {
    while(!shouldExit_) {
        std::string cmd;
        getline(in_, cmd);
        std::stringstream ss(cmd);
        dispatchCommand(ss);
    }
}

void ImuDispatcher::dispatchCommand(std::stringstream& cmdString) {
    std::string cmd;
    cmdString >> cmd;
    if(cmd == "getAcceleration") _getAcceleration();
    else if(cmd == "getAngularAcceleration") _getAngularAcceleration();
    else if(cmd == "getHeading") _getHeading();
    else if(cmd == "getInternalTemperature") _getInternalTemperature();
    else if(cmd == "getInternalPressure") _getInternalPressure();
}

void ImuDispatcher::_getAcceleration() {
    auto data = imuSensor_.getAcceleration();
    auto accelJson = json{
            {"Type", "Acceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    out_ << accelJson << std::endl;
}

void ImuDispatcher::_getAngularAcceleration() {
    auto data = imuSensor_.getAngularAcceleration();
    auto accelJson = json{
            {"Type", "AngularAcceleration"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)},
            {"Z", std::get<2>(data)}
    };
    out_ << accelJson << std::endl;
}

void ImuDispatcher::_getHeading() {
    auto data = imuSensor_.getHeading();
    auto headingJson = json{
            {"Type", "Heading"},
            {"X", std::get<0>(data)},
            {"Y", std::get<1>(data)}//,
            //{"Z", std::get<2>(data)}
    };
    out_ << headingJson << std::endl;
}

void ImuDispatcher::_getInternalTemperature() {
    auto data = imuSensor_.getIntTemperature();
    out_ << json{{"Type", "InternalTemperature"},{"Value",data}} << std::endl;
}

void ImuDispatcher::_getInternalPressure() {
    auto data = imuSensor_.getIntPressure();
    out_ << json{{"Type", "InternalPressure"},{"Value",data}} << std::endl;
}

void ImuDispatcher::stopListening() {
    shouldExit_ = true;
}

ImuDispatcher::~ImuDispatcher() {
    thread_.join();
}
