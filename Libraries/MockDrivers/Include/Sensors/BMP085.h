/**
  * \class BMP085
  *
  *  Created on: Jan 29, 2015
  * Last Edited: Feb  7, 2016
  *        Fork: https://github.com/adafruit/Adafruit-BMP085-Library
  *
  * \brief This is a hardware wrapper for the BMP085 pressure sensor.
  *        It provides fundimental sensor readings and control in  an  orginized
  *        manner.
  */

#ifndef BMP085_H_
#define BMP085_H_

#include "I2C.h"
#include "BMP085_Reg.h"
#include "IDriver.h"

#include <chrono>
#include <thread>
#include <cmath>

#define delay(time) std::this_thread::sleep_for(std::chrono::milliseconds(time));

class BMP085 : public IDriver
{
    public:
        /** \brief Initializes a new pressure  sensor  for  depth  and  altitude
          *        analysis.
          * \param bus The address of the I2C bus the sensor listens on.
          */
        BMP085();
        virtual ~BMP085();

        /** \brief Takes an ID reading from the sensor.
         *  \return Returns the ID associated with the BMP085 device (0x55).
         */
        int WhoAmI();

        /** \brief Initializes  the  environment  and  establishes   calibration
          *        constants used in future computations.
          * \param mode The mode used to determine the accuracy of measurements.
          * \return Returns true if initialization was successful.
          */
        bool initialize(uint8_t mode = BMP085_STANDARD);

        /** \brief Makes a temperature reading from the sensor.
          * \return Returns a measurement in °C with an accuracy of ± 0.1.
          */
        float readTemperature();

        /** \brief Makes a pressure reading from the sensor.
          * \return Returns a measurement in Pascals (Pa)
          */
        int32_t readPressure();

        /** \brief Makes a pressure reading calculated at sealevel.
          * \param Optionally provide  an  altitude  in  meters  describing  the
          *        sensor's position.
          * \return Returns a measurement in Pascals (Pa)
          */
        int32_t readSealevelPressure(float altitude_meters = 0);

        // read the approximate altitude in meters (m)
        // params: current provided sea level pressure
        /** \brief Makes a pressure reading and calculates the current altitude.
          * \param sealevelPressure The  measured  sealevel  pressure   of   the
          *        environment.
          * \return Returns the altitude in meters.
          */
        float readAltitude(float sealevelPressure = 101325);

    private:
        // apply compensation
        int32_t computeB5(int32_t UT);

        // bit swap to correct endianness
        uint16_t endian16(uint16_t x);
        uint8_t endian8(uint8_t x);

        // read raw sensor data
        /** \brief Returns the raw sensor data for temperature.
          */
        uint16_t readRawTemperature(void);

        /** \brief Returns the raw sensor data for pressure.
          */
        uint32_t readRawPressure(void);

        int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
        uint16_t ac4, ac5, ac6;
        uint8_t oversampling;
};

#endif /* BMP085_H_ */
