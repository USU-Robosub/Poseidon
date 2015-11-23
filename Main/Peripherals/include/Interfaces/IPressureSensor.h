//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_PRESSURE_SENSOR_H
#define PERIPHERALS_I_PRESSURE_SENSOR_H

#include <cstdint>

class IPressureSensor {
public:
    virtual bool initialize(uint8_t mode) = 0;
    virtual float readTemperature(void) = 0;
    virtual int32_t readPressure(void) = 0;
    virtual int32_t readSealevelPressure(float altitude_meters) = 0;
    virtual float readAltitude(float sealevelPressure) = 0;
};

#endif //PERIPHERALS_I_PRESSURE_SENSOR_H
