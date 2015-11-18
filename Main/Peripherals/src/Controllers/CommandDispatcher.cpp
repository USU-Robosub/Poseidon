//
// Created by Nathan Copier on 11/10/2015.
//

#include "Controllers/CommandDispatcher.h"

void dispatchCommands( std::istream& in, ThrustController& thrustController );

CommandDispatcher::CommandDispatcher( std::istream& in, ThrustController& thrustController ) {
    auto thread = std::thread( [&](){ dispatchCommands(in, thrustController); } );
    thread.join();
};

void dispatchCommands( std::istream& in, ThrustController& thrustController )
{
    while (true) {
        std::string command;
        int activeThrottle;
        in >> command;
        in >> activeThrottle;
        if(command == "dive")
        {
            thrustController.setDiveThrust(activeThrottle);
        }
        else if(command == "forward")
        {
            thrustController.setForwardThrust(activeThrottle);
        }
        else if(command == "yaw")
        {
            thrustController.setYawThrust(activeThrottle);
        }
    }
}
