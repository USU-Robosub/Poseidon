//
// Created by Nathan Copier on 4/26/2016.
//

#include "ImuDispatcher.h"

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
    if(cmd == "getAcceleration") {
        auto data = imuSensor_.getAcceleration();
        out_ << std::get<0>(data) << " " << std::get<1>(data) << " " << std::get<2>(data) << " " << std::endl;
    }
}

void ImuDispatcher::stopListening() {
    shouldExit_ = true;
}

ImuDispatcher::~ImuDispatcher() {
    thread_.join();
}
