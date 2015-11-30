//
// Created by Nathan Copier on 11/10/2015.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include "ThrustController.h"
#include <istream>
#include <thread>
#include <string>


class CommandDispatcher {

public:

    CommandDispatcher( std::istream& in, ThrustController& thrustController );

};


#endif //PERIPHERALS_COMMAND_DISPATCHER_H
