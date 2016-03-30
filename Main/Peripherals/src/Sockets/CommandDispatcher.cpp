//
// Created by Nathan Copier on 1/28/2016.
//

#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(ThrustController& thrustController, PowerManager& powerManager, IHeadlights& lights)
        : thrustController_(thrustController), powerManager_(powerManager), lights_(lights), shouldExit_(false) {}

void CommandDispatcher::runLoop(std::istream& in) {
    while(!shouldExit_) {
        std::string cmd;
        std::getline(in, cmd);
        std::stringstream ss(cmd);
        if(!run(ss))
            shouldExit_ = true;
    }
}

int CommandDispatcher::run(std::stringstream& ss) {
    return dispatchCommand(ss);
}

int CommandDispatcher::dispatchCommand(std::stringstream& cmdString) {
    std::string cmd;
    cmdString >> cmd;
    if(cmd == "goDirection") goDirection(cmdString);
    else if(cmd == "faceDirection") faceDirection(cmdString);
    else if(cmd == "turnOnEscs") powerManager_.turnOnEscs();
    else if(cmd == "turnOffEscs") powerManager_.turnOffEscs();
    else if(cmd == "switchLights") lights_.switchLights();
    else if(cmd == "exit") return 0;
    return 1;
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
