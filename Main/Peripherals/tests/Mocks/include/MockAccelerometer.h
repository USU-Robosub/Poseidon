//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_ACCELEROMETER_H
#define PERIPHERALS_MOCK_ACCELEROMETER_H

#include <IAccelerometer.h>
#include <tuple>

class MockAccelerometer : public IAccelerometer {
public:
    std::tuple<float, float, float> getAcceleration()
    {
        return std::make_tuple(0, 0, 0);
    }
    void setMagnitude(int magnitudeOption) {}
};


#endif //PERIPHERALS_MOCK_ACCELEROMETER_H
