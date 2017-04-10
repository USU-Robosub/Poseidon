//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_PRESSURE_SENSOR_H
#define PERIPHERALS_I_PRESSURE_SENSOR_H

class IPressureSensor {
public:
    virtual double getPressure() = 0;
};

#endif //PERIPHERALS_I_PRESSURE_SENSOR_H
