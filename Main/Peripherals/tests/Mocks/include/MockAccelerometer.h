//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_ACCELEROMETER_H
#define PERIPHERALS_MOCK_ACCELEROMETER_H

#include <IAccelerometer.h>

class MockAccelerometer : public IAccelerometer {
public:
    int16_t accel_X(){}
    int16_t accel_Y(){}
    int16_t accel_Z(){}
    int16_t gyro_X(){}
    int16_t gyro_Y(){}
    int16_t gyro_Z(){}
    float temp(){}
    void sleep(){}
    void awake(){}
};


#endif //PERIPHERALS_MOCK_ACCELEROMETER_H
