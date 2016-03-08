#include "MPU6050.h"
#include "ITemperatureSensor"

#include <memory>

class TemperatureSensor : public ITemperatureSensor {
public:
    TemperatureSensor(std::shared_ptr<MPU6050> temperatureSensor);
    float getTempreature();
private:
    std::shared_ptr<MPU6050> temperatureSensor_;
};
