//
// Created by Nathan Copier on 11/20/2015.
// Updated by TekuConcept on 4/10/2015.
//

#ifndef PERIPHERALS_I_PRESSURE_SENSOR_H
#define PERIPHERALS_I_PRESSURE_SENSOR_H

#include "ICalibratable.h"

class IPressureSensor : public ICalibratable {
public:
    virtual double getPressure() = 0;
};

#endif //PERIPHERALS_I_PRESSURE_SENSOR_H
