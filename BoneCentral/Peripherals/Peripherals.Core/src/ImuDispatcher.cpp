//
// Created by Nathan Copier on 4/26/2016.
//

#include "ImuDispatcher.h"

ImuDispatcher::ImuDispatcher(ImuSensor& imuSensor, std::istream& in, std::ostream& out) {
    while(true) {
        std::string cmd;
        std::getline(in, cmd);
        std::stringstream ss(cmd);
        dispatchCommand(ss, out, imuSensor);
    }
}

void ImuDispatcher::dispatchCommand(std::stringstream& cmdString, std::ostream& out, ImuSensor& imuSensor) {
    std::string cmd;
    cmdString >> cmd;
    if(cmd == "getAcceleration") {
        auto data = imuSensor.getAcceleration();
        out << std::get<0>(data) << " " << std::get<1>(data) << " " << std::get<2>(data) << " " << std::endl;
    }
}
