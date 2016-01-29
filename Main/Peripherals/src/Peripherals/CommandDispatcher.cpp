//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(std::istream& in, ThrustController& thrustController) : thrustController_(thrustController) {
    while(true) {
        std::string cmd;
        std::getline(in, cmd);
        dispatchCommand(std::stringstream(cmd));
    }
}

void CommandDispatcher::dispatchCommand(std::stringstream cmdString) {
    std::string cmd;
    cmdString >> cmd;
    if(cmd == "goDirection") {
        float forward, strife, dive;
        cmdString >> forward;
        cmdString >> strafe;
        cmdString >> dive;
        thrustController_.goDirection(forward, strafe, dive);
    }
    else if(cmd == "faceDirection") {
        float yaw;
        cmdString << yaw;
        thrustController_.yaw(yaw);
    }
}