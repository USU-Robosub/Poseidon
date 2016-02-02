/**
  * \class MPU6050
  *
  *  Created on: Feb 2, 2015
  *      Author: TekuConcept
  *
  * \brief This is a hardware wrapper for the MPU6050 Accelerometer sensor.
  *        It provides fundimental sensor readings and control.
  */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "Constants.h"
#include "stdint.h"

class MPU6050
{
    public:
        /// FS_SEL selects the full scale range of the gyroscope outputs according to the following table.
        enum FS_SEL
        { // ± °/s
            FSG_250 = 0, ///< ± 250 °/s
            FSG_500,     ///< ± 500 °/s
            FSG_1K,      ///< ± 1000 °/s
            FSG_2K       ///< ± 2000 °/s
        };

        /// AFS_SEL selects the full scale range of the accelerometer outputs according to the following table.
        enum AFS_SEL
        { // ± g
            FSA_2 = 0,   ///< ± 2g
            FSA_4,       ///< ± 4g
            FSA_8,       ///< ± 8g
            FSA_16       ///< ± 16g
        };

        /** \brief Initializes a new accelerometer sensor for motion-based analysis
          * \param bus The address of the I2C bus the accelerometer listens on.
          */
        MPU6050();
        virtual ~MPU6050();


        // returns the XYZ magnitude from accelerometer
        /** \brief Makes a reading from the accelerometer's X axis.
          * \return Returns a signed short representation of the acceleration.
          */
        int16_t accel_X();

        /** \brief Makes a reading from the accelerometer's Y axis.
          * \return Returns a signed short representation of the acceleration.
          */
        int16_t accel_Y();

        /** \brief Makes a reading from the accelerometer's Z axis.
          * \return Returns a signed short representation of the acceleration.
          */
        int16_t accel_Z();

        // returns the XYZ magnitude from gyroscope
        /** \brief Makes a reading from the gyroscope's X axis.
          * \return Returns a signed short representation of the angle.
          */
        int16_t gyro_X();

        /** \brief Makes a reading from the gyroscope's Y axis.
          * \return Returns a signed short representation of the angle.
          */
        int16_t gyro_Y();

        /** \brief Makes a reading from the gyroscope's Z axis.
          * \return Returns a signed short representation of the angle.
          */
        int16_t gyro_Z();

        // returns the temperature of the sensor's environment
        /** \brief Makes a temperature reading from the sensor.
          * \return Returns a measurement in °C with an accuracy of ± 0.01.
          */
        float temp();


        // FS_SEL selects the full scale range of the gyroscope outputs
        /** \brief Sets the full scale range of the gyroscope.
          * \param select Selects the full scale range of the gyroscope outputs according to the definitions of the FS_SEL enum.
          */
        void setGyroFullScale(FS_SEL select);

        // AFS_SEL selects the full scale range of the accelerometer outputs
        /** \brief Sets the full scale range of the accelerometer.
          * \param select Selects the full scale range of the accelerometer outputs according to the definitions of the AFS_SEL enum.
          */
        void setAcclFullScale(AFS_SEL select);

        /** \brief Puts the device into a power-saving sleep mode.
          */
        void sleep();
        /** \brief Puts the device into an active reading mode.
          */
        void awake();

    public:
        uint8_t readByte(uint8_t addr);
        uint16_t read16(uint8_t addr);
        void writeByte(uint8_t addr, uint8_t data);
};

#endif

