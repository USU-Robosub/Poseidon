/**
  * \class IMUSensor
  *
  *  Created on: Jan 18, 2015
  *      Author: Jesse Victors
  *
  * \brief This is an API object designed as a way to provide a user with many forms of simple sensor readings.
  *        Sensors currently available include: BMP085 (pressure), HMC5883L (compass), and MPU6050 (accelerometer & gyroscope).
  */

#ifndef IMU_SENSOR
#define IMU_SENSOR

#include <memory>
#include <mutex>
#include <chrono>
#include <thread>
#include <fstream>

#include "ILogger.h"
#include "IImuFactory.h"
#include "IPressureSensor.h"

class IMUSensor
{
    public:
        /** \brief Initializes a new instance of a sensor interface.
          */
        IMUSensor(IImuFactory& imuFactory, std::shared_ptr<ILogger> logger);
        ~IMUSensor();

        /** \brief Returns the temperature reading from the BMP085 sensor in ± 0.1°C.
          */
        float readTemperature();

        /** \brief Returns the pressure reading from the BMP085 sensor in Pascals (Pa).
          */
        int32_t readPressure();

        /** \brief Returns the calculated sealevel from the BMP085 sensor in Pascals (Pa)
          * \param altitudeMeters [optional] The base altitude of the sensor represented in meters above sealevel.
          */
        int32_t readSealevel(float altitudeMeters = 0);

        // Logan Utah: 101929 mB
        /** \brief Returns the calculated altitude reading from the BMP085 sensor in meters (m).
          * \param sealevelPressure [optional] The approximate sealevel pressure at the sensor's location.
          */
        float readAltitude(float sealevelPressure = 101929);

        /** \brief Returns the X-axis reading from the HMC5883L sensor.
          */
    	int16_t readCompassX();

        /** \brief Returns the Y-axis reading from the HMC5883L sensor.
          */
    	int16_t readCompassY();

        /** \brief Returns the Z-axis reading from the HMC5883L sensor.
          */
    	int16_t readCompassZ();

        /** \brief Returns the X-axis reading from the MPU6050's accelerometer.
          */
    	int16_t readAccelX();

        /** \brief Returns the Y-axis reading from the MPU6050's accelerometer.
          */
    	int16_t readAccelY();

        /** \brief Returns the Z-axis reading from the MPU6050's accelerometer.
          */
    	int16_t readAccelZ();

        /** \brief Returns the X-axis reading from the MPU6050's gyroscope.
          */
    	int16_t readGyroX();

        /** \brief Returns the Y-axis reading from the MPU6050's gyroscope.
          */
    	int16_t readGyroY();

        /** \brief Returns the Z-axis reading from the MPU6050's gyroscope.
          */
    	int16_t readGyroZ();

        /** \brief Returns the temperature reading from the MPU6050 sensor in ± 0.01°C.
          */
        float getTemp();

        /** \brief Puts the MPU6050 sensor into active-recording mode.
          */
        void turnOn();

        /** \brief Puts the MPU6050 sensor into power-saving mode.
          */
        void turnOff();

    private:

        std::shared_ptr<ILogger> logger_;
        std::shared_ptr<IPressureSensor> pressureSensor_;
        std::shared_ptr<ICompass> compass_;
        std::shared_ptr<IAccelerometer> accelerometer_;
        std::mutex sensorMutex_;
};

#endif
