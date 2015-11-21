/**
  * \class BMP085
  *
  *  Created on: Jan 29, 2015
  *  Fork: https://github.com/adafruit/Adafruit-BMP085-Library
  *
  * \brief This is a hardware wrapper for the BMP085 pressure sensor.
  *        It provides fundimental sensor readings and control in an orginized manner.
  */

#ifndef BMP085_H_
#define BMP085_H_

#include "IPressureSensor.h"
#include "I2C/I2C.h"
#include "IMU_Const.h"
#include "stdint.h"
#include <chrono>
#include <thread>
#include <cmath>


class BMP085 : public IPressureSensor
{
    public:
        /** \brief Initializes a new pressure sensor for depth and altitude analysis.
          * \param bus The address of the I2C bus the sensor listens on.
          */
        BMP085(uint _bus_);
        virtual ~BMP085();

        /** \brief Initializes the environment and establishes calibration constants used in future computations.
          * \param mode The mode used to determine the accuracy of measurements.
          * \return Returns true if initialization was successful.
          */
        virtual bool initialize(uint8_t mode = IMU_ENVIRONMENT_ULTRAHIGHRES);

        /** \brief Makes a temperature reading from the sensor.
          * \return Returns a measurement in °C with an accuracy of ± 0.1.
          */
        virtual float readTemperature(void);

        /** \brief Makes a pressure reading from the sensor.
          * \return Returns a measurement in Pascals (Pa)
          */
        virtual int32_t readPressure(void);

        /** \brief Makes a pressure reading calculated at sealevel.
          * \param Optionally provide an altitude in meters describing the sensor's position.
          * \return Returns a measurement in Pascals (Pa)
          */
        virtual int32_t readSealevelPressure(float altitude_meters = 0);

        // read the approximate altitude in meters (m)
        // params: current provided sea level pressure
        /** \brief Makes a pressure reading and calculates the current altitude.
          * \param sealevelPressure The measured sealevel pressure of the environment.
          * \return Returns the altitude in meters.
          */
        virtual float readAltitude(float sealevelPressure = 101325);

        // read raw sensor data
        /** \brief Returns the raw sensor data for temperature.
          */
        uint16_t readRawTemperature(void);

        /** \brief Returns the raw sensor data for pressure.
          */
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

        void print_debug();

        I2C bus;
        int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
        uint16_t ac4, ac5, ac6;
        uint8_t oversampling;
};

#endif /* BMP085_H_ */
