//
// Created by Nathan Copier on 11/21/2015.
// Last edited by Kevin Burgon on 03/08/2016.
//

#ifndef PERIPHERALS_I_ACCELEROMETER_H
#define PERIPHERALS_I_ACCELEROMETER_H

#include <tuple>

class IAccelerometer {
public:
    virtual std::tuple<float, float, float> getAcceleration() = 0;
    virtual void setMagnitude(int magnitudeOption) = 0;
};

#endif //PERIPHERALS_I_ACCELEROMETER_H
