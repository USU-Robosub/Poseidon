//
// Created by Nathan Copier on 11/10/2015.
//

#include "CommandDispatcher.h"

void dispatchCommands( std::istream& in, ThrustController& thrustController );

CommandDispatcher::CommandDispatcher( std::istream& in, ThrustController& thrustController ) {
    auto thread = std::thread( [&](){ dispatchCommands(in, thrustController); } );
    thread.join();
}

void dispatchCommands( std::istream& in, ThrustController& thrustController )
{
    while (true) {
        std::string command;
        int powerLevel;
        in >> command;
        in >> powerLevel;
        if(command == "dive")
        {
            thrustController.setDiveThrust(powerLevel);
        }
        else if(command == "forward")
        {
            thrustController.setForwardThrust(powerLevel);
        }
        else if(command == "yaw")
        {
            thrustController.setYawThrust(powerLevel);
        }
    }
}
