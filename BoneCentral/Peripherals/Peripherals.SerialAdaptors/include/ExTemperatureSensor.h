#ifndef DRIVER_EX_TEMPERATURE_SENSOR
#define DRIVER_EX_TEMPERATURE_SENSOR

#include <ITemperatureSensor.h>
#include "Serial.h"
#include "ArduinoConfig.h"

class ExTemperatureSensor : public ITemperatureSensor {
private:
    Serial& serial_;
public:
    ExTemperatureSensor(Serial& serial);
    double getTemperature();
private:
};

#endif
