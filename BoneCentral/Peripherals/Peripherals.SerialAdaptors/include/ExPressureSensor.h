#ifndef DRIVER_EX_PRESSURE_SENSOR
#define DRIVER_EX_PRESSURE_SENSOR

#include <IPressureSensor.h>
#include "Serial.h"
#include "ArduinoConfig.h"

class ExPressureSensor : public IPressureSensor {
private:
    Serial& serial_;
public:
    ExPressureSensor(Serial& serial);
    double getPressure();
};

#endif
