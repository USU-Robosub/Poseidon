#ifndef DRIVER_IN_TEMPERATURE_2_SENSOR
#define DRIVER_IN_TEMPERATURE_2_SENSOR

#include "BMP085.h"
#include "ITemperatureSensor.h"
#include <memory>

class TemperatureSensor : public ITemperatureSensor {
public:
    TemperatureSensor(std::shared_ptr<BMP085> temperatureSensor);
    float getTemperature();
private:
    std::shared_ptr<BMP085> temperatureSensor_;
};

#endif
