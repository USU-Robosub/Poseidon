//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(std::istream& in, ThrustController& thrustController, PowerManager& powerManager)
        : thrustController_(thrustController), powerManager_(powerManager) {
    while(true) {
        std::string cmd;
        std::getline(in, cmd);
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