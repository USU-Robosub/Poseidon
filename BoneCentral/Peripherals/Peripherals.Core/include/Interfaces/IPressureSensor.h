//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_PRESSURE_SENSOR_H
#define PERIPHERALS_I_PRESSURE_SENSOR_H

#include <cstdint>

class IPressureSensor {
public:
    virtual int getPressure(void) = 0;
};

#endif //PERIPHERALS_I_PRESSURE_SENSOR_H
