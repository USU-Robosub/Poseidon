//
// Created by Nathan Copier on 11/10/2015.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
#include "IHeadlights.h"
#include <istream>
#include <thread>
#include <string>


class CommandDispatcher {

public:

    CommandDispatcher( std::istream& in, ThrustController& thrustController );

private:

    std::shared_ptr<IHeadlights> lights_;
    
};


#endif //PERIPHERALS_COMMAND_DISPATCHER_H
