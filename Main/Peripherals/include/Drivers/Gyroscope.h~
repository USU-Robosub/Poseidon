#ifndef DRIVERS_GYROSCOPE_H
#define DRIVERS_GYROSCOPE_H

#include "MPU6050.h"
#include "IGyroscope.h"

#include <memory>
#include <utility>
#include <tuple>

typedef std::tuple<float, float, float> FloatTuple;

class Gyroscope : public IGyroscope {
public:
    Gyroscope(std::shared_ptr<MPU6050> gyroscope);
    FloatTuple getAngularAcceleration();
    void setMagnitude(int magnitudeOption);
private:
    std::shared_ptr<MPU6050> gyroscope_;
};

#endif
