#ifndef DRIVER_EX_TEMPERATURE_SENSOR
#define DRIVER_EX_TEMPERATURE_SENSOR

// Arduino Temperature Sensor
#include "ITemperatureSensor.h"
#include <memory>

class TemperatureSensor : public ITemperatureSensor {
public:
    TemperatureSensor();
    float getTemperature();
private:
};

#endif
