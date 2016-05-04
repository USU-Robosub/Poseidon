//
// Created by Nathan Copier on 4/26/2016.
//

#ifndef PERIPHERALS_IMU_DISPATCHER_H
#define PERIPHERALS_IMU_DISPATCHER_H

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <atomic>
#include <json.h>
#include "ImuSensor.h"


class ImuDispatcher {
public:
    ImuDispatcher(ImuSensor& imuSensor, std::istream& in, std::ostream& out);
    void startListening();
    void stopListening();
    ~ImuDispatcher();

private:
    void _runLoop();
    void dispatchCommand(std::stringstream& cmdString);
    void _getAcceleration();
    void _getAngularAcceleration();
    void _getHeading();
    void _getInternalTemperature();
    void _getInternalPressure();
    void _getExternalTemperature();
    void _getExternalPressure();

    std::thread thread_;
    ImuSensor& imuSensor_;
    std::istream& in_;
    std::ostream& out_;
    std::atomic_bool shouldExit_;
};


#endif //PERIPHERALS_IMU_DISPATCHER_H
