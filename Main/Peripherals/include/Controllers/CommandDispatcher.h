//
// Created by Nathan Copier on 11/10/2015.
//

#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include <istream>
#include <thread>
#include <string>
#include "ThrustController.h"


class CommandDispatcher {

public:

    CommandDispatcher( std::istream& in, ThrustController& thrustController );

};


#endif //PERIPHERALS_COMMAND_DISPATCHER_H
