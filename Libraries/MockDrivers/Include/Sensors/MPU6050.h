/**
  * \class MPU6050
  *
  *  Created on: Feb 2, 2015
  * Last Edited: Feb 7, 2016
  *      Author: TekuConcept
  *
  * \brief This is a hardware wrapper for the MPU6050 Accelerometer sensor.
  *        It provides fundimental sensor readings and control in  an  orginized
  *        manner.
  */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "I2C.h"
#include "MPU6050_Reg.h"
#include "IDriver.h"
#include <stdexcept>

class MPU6050 : public IDriver
{
    public:
        /** \brief Initializes  a  new  accelerometer  sensor  for  motion-based
          *        analysis
          * \param bus The address of the I2C bus the accelerometer listens on.
          */
        MPU6050();
        virtual ~MPU6050();

        /** \brief Takes an ID reading from the sensor.
         *  \return Returns the ID associated with the MPU6050 device (0x68).
         */
        int WhoAmI();
        
        
    
        /**********************************************************************/
        /*                        Configuration Enums                         */
        /**********************************************************************/
        
        /// FS_SEL selects  the  full  scale  range  of  the  gyroscope  outputs
        /// according to the following table.
        enum class FS_SEL
        { // ± °/s
            FSG_250 = 0, ///< ± 250 °/s
            FSG_500,     ///< ± 500 °/s
            FSG_1K,      ///< ± 1000 °/s
            FSG_2K       ///< ± 2000 °/s
        };

        /// AFS_SEL selects the full scale range of  the  accelerometer  outputs
        /// according to the following table.
        enum class AFS_SEL
        { // ± g
            FSA_2 = 0,   ///< ± 2g
            FSA_4,       ///< ± 4g
            FSA_8,       ///< ± 8g
            FSA_16       ///< ± 16g
        };
        
        
        
        /**********************************************************************/
        /*                           Sensor Values                            */
        /**********************************************************************/

        // returns the XYZ magnitude from accelerometer
        /** \brief Makes a reading from the accelerometer's X axis.
          * \return Returns a signed short representation of the acceleration.
          */
        float accel_X();

        /** \brief Makes a reading from the accelerometer's Y axis.
          * \return Returns a signed short representation of the acceleration.
          */
        float accel_Y();

        /** \brief Makes a reading from the accelerometer's Z axis.
          * \return Returns a signed short representation of the acceleration.
          */
        float accel_Z();

        // returns the XYZ magnitude from gyroscope
        /** \brief Makes a reading from the gyroscope's X axis.
          * \return Returns a signed short representation of the angle.
          */
        float gyro_X();

        /** \brief Makes a reading from the gyroscope's Y axis.
          * \return Returns a signed short representation of the angle.
          */
        float gyro_Y();

        /** \brief Makes a reading from the gyroscope's Z axis.
          * \return Returns a signed short representation of the angle.
          */
        float gyro_Z();

        // returns the temperature of the sensor's environment
        /** \brief Makes a temperature reading from the sensor.
          * \return Returns a measurement in °C with an accuracy of ± 0.01.
          */
        float temperature();



        /**********************************************************************/
        /*                           Configuration                            */
        /**********************************************************************/

        // FS_SEL selects the full scale range of the gyroscope outputs
        /** \brief Sets the full scale range of the gyroscope.
          * \param select Selects the full scale range of the gyroscope  outputs
          *        according to the definitions of the FS_SEL enum.
          */
        void setGyroFullScale(FS_SEL select);

        // AFS_SEL selects the full scale range of the accelerometer outputs
        /** \brief Sets the full scale range of the accelerometer.
          * \param select Selects the full  scale  range  of  the  accelerometer
          *        outputs according to the definitions of the AFS_SEL enum.
          */
        void setAcclFullScale(AFS_SEL select);

        /** \brief Puts the device into a power-saving sleep mode.
          */
        void sleep();
        
        /** \brief Puts the device into an active reading mode.
          */
        void awake();

    private:
        FS_SEL g_full;
        AFS_SEL a_full;

        const float GYRO_SCALER[4]= { 131.0, 65.5, 32.8, 16.4 }; // LSb / °/s
        const int ACCEL_SCALER[4] = { 16384, 8192, 4096, 2048 }; // LSb / g

        /** \brief Scales the raw data (LSb) with the current scalar (LSb / °/s)
         *  \param value Raw data that needs to be scaled
         */
        float scaleGyro(short value);

        /** \brief Scales the raw data (LSb) with the current scalar (LSb / g)
         *  \param value Raw data that needs to be scaled
         */
        float scaleAccel(short value);
};

#endif /* MPU6050_H_ */
