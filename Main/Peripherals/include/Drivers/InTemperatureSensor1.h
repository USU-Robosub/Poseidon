#ifndef DRIVER_IN_TEMPERATURE_1_SENSOR
#define DRIVER_IN_TEMPERATURE_1_SENSOR

#include "MPU6050.h"
#include "ITemperatureSensor.h"
#include <memory>

class TemperatureSensor : public ITemperatureSensor {
public:
    TemperatureSensor(std::shared_ptr<MPU6050> temperatureSensor);
    float getTemperature();
private:
    std::shared_ptr<MPU6050> temperatureSensor_;
};

#endif