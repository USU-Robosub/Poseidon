//
// Created by Nathan Copier on 11/21/2015.
//

#ifndef PERIPHERALS_I_ACCELEROMETER_H
#define PERIPHERALS_I_ACCELEROMETER_H

class IAccelerometer {
public:
    virtual int16_t accel_X() = 0;
    virtual int16_t accel_Y() = 0;
    virtual int16_t accel_Z() = 0;
    virtual int16_t gyro_X() = 0;
    virtual int16_t gyro_Y() = 0;
    virtual int16_t gyro_Z() = 0;
    virtual float temp() = 0;
    virtual void sleep() = 0;
    virtual void awake() = 0;
};

#endif //PERIPHERALS_I_ACCELEROMETER_H
