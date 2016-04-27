//
// Created by Nathan Copier on 4/26/2016.
//

#ifndef PERIPHERALS_IMU_DISPATCHER_H
#define PERIPHERALS_IMU_DISPATCHER_H

#include <iostream>
#include <string>
#include <sstream>
#include "ImuSensor.h"


class ImuDispatcher {
public:
    ImuDispatcher(ImuSensor& imuSensor, std::istream& in, std::ostream& out);

private:
    void dispatchCommand(std::stringstream& cmdString, std::ostream& out, ImuSensor& imuSensor);
};


#endif //PERIPHERALS_IMU_DISPATCHER_H
