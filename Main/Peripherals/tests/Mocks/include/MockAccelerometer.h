//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_ACCELEROMETER_H
#define PERIPHERALS_MOCK_ACCELEROMETER_H

#include <IAccelerometer.h>

class MockAccelerometer : public IAccelerometer {
public:
    float accel_X(){ return 0; }
    float accel_Y(){ return 0; }
    float accel_Z(){ return 0; }
    float gyro_X(){ return 0; }
    float gyro_Y(){ return 0; }
    float gyro_Z(){ return 0; }
    float temp(){ return 0; }
    void sleep(){}
    void awake(){}
};


#endif //PERIPHERALS_MOCK_ACCELEROMETER_H
