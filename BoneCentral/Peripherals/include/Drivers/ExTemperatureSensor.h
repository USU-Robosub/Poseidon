#ifndef DRIVER_EX_TEMPERATURE_SENSOR
#define DRIVER_EX_TEMPERATURE_SENSOR

// Arduino Temperature Sensor
#include "ITemperatureSensor.h"
#include <memory>

class ExTemperatureSensor : public ITemperatureSensor {
public:
    ExTemperatureSensor();
    float getTemperature();
private:
};

#endif
