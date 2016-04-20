#ifndef INTERFACES_I_GYROSCOPE_H
#define INTERFACES_I_GYROSCOPE_H

#include <tuple>

class IGyroscope {
public:
    virtual std::tuple<float, float, float> getAngularAcceleration() = 0;
    virtual void setMagnitude(int magnitudeOption) = 0;
};

#endif
