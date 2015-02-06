/*
 * MPU6050.h
 *
 *  Created on: Feb 2, 2015
 *      Author: TekuConcept
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "../I2C/I2C.h"
#include "IMU_Const.h"
#include "stdint.h"
#include <stdexcept>

class MPU6050
{
    public:

        enum FS_SEL
        { // ± °/s
            FSG_250 = 0, FSG_500, FSG_1K, FSG_2K
        };

        enum AFS_SEL
        { // ± g
            FSA_2 = 0, FSA_4, FSA_8, FSA_16
        };


        MPU6050(uint _bus_);
        virtual ~MPU6050();


        // returns the XYZ magnitude from accelerometer
        int16_t accel_X();
        int16_t accel_Y();
        int16_t accel_Z();

        // returns the XYZ magnitude from gyroscope
        int16_t gyro_X();
        int16_t gyro_Y();
        int16_t gyro_Z();

        // returns the temperature of the sensor's environment
        int16_t temp();


        // FS_SEL selects the full scale range of the gyroscope outputs
        void setGyroFullScale(FS_SEL select);

        // AFS_SEL selects the full scale range of the accelerometer outputs
        void setAcclFullScale(AFS_SEL select);

        void sleep(); // puts the device to sleep
        void awake(); // wakes the device and starts capturing

    private:
        I2C bus;
};

#endif /* MPU6050_H_ */
