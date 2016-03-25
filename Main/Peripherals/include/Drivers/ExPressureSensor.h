#ifndef DRIVER_EX_PRESSURE_SENSOR
#define DRIVER_EX_PRESSURE_SENSOR

// Arduino Pressure Sensor
#include "IPressureSensor.h"
#include <memory>

class ExPressureSensor : public IPressureSensor {
public:
    ExPressureSensor();
    int getPressure();
private:
};

#endif
