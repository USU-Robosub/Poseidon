/*
 * BMP085.h
 *
 *  Created on: Jan 29, 2015
 *  Fork: https://github.com/adafruit/Adafruit-BMP085-Library
 */

#ifndef BMP085_H_
#define BMP085_H_

#include "../I2C/I2C.h"
#include "IMU_Const.h"
#include "stdint.h"
#include <chrono>
#include <thread>


class BMP085
{
    public:
        BMP085(uint _bus_);
        virtual ~BMP085();

        bool initialize(uint8_t mode = IMU_ENVIRONMENT_ULTRAHIGHRES);

        // read the approximate temperature in celsius (C)
        float readTemperature(void);

        // read the approximate pressure in pascals (Pa)
        int32_t readPressure(void);

        // read the pressure at sea level in pascals (Pa)
        // params: current provided position in meters
        int32_t readSealevelPressure(float altitude_meters = 0);

        // read the approximate altitude in meters (m)
        // params: current provided sea level pressure
        float readAltitude(float sealevelPressure = 101325);

        // read raw sensor data
        uint16_t readRawTemperature(void);
        uint32_t readRawPressure(void);

    private:
        // read a byte from the sensor
        // params: register address
        uint8_t read8(uint8_t addr);

        // read a short from the sensor
        // params: register address
        uint16_t read16(uint8_t addr);

        // write a byte to the sensor
        // params: register address, data to be written
        void write8(uint8_t addr, uint8_t data);

        // apply compensation
        int32_t computeB5(int32_t UT);

        // bit swap to correct endianness
        uint16_t endian16(uint16_t x);
        uint8_t endian8(uint8_t x);

        I2C bus;
        int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
        uint16_t ac4, ac5, ac6;
        uint8_t oversampling;
};

#endif /* BMP085_H_ */
