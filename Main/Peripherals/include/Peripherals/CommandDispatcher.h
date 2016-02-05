//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
<<<<<<< HEAD
#include "IHeadlights.h"
=======
#include "PowerManager.h"

>>>>>>> develop
#include <istream>
#include <string>
#include <sstream>

class CommandDispatcher {
private:
    std::istream& in_;
    ThrustController& thrustController_;
    PowerManager& powerManager_;
    void dispatchCommand(std::stringstream& cmd);
    void goDirection(std::stringstream& cmdString);
    void faceDirection(std::stringstream& cmdString);
public:
<<<<<<< HEAD

    CommandDispatcher( std::istream& in, ThrustController& thrustController );

private:

    std::shared_ptr<IHeadlights> lights_;
    
=======
    CommandDispatcher(std::istream& in, ThrustController& thrustController, PowerManager& powerManager);
    void runLoop();
>>>>>>> develop
};

#endif //PERIPHERALS_COMMAND_DISPATCHER_H
