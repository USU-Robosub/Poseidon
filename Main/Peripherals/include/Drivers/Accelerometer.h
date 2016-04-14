#ifndef DRIVERS_ACCELEROMETER_H
#define DRIVERS_ACCELEROMETER_H

#include "MPU6050.h"
#include "IAccelerometer.h"

#include <memory>
#include <utility>
#include <tuple>

typedef std::tuple<float, float, float> FloatTuple;

class Accelerometer : public IAccelerometer {
public:
    Accelerometer(std::shared_ptr<MPU6050> accelerometer);
    FloatTuple getAcceleration();
    void setMagnitude(int magnitudeOption);
private:
    std::shared_ptr<MPU6050> accelerometer_;
};

#endif
