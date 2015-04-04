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

//#include "rice/Array.hpp"
#include "../drivers/IMU/BMP085.h"
#include "../drivers/IMU/HMC5883L.h"
#include "../drivers/IMU/MPU6050.h"
#include "../Environment.h"
#include <memory>
#include <mutex>
#include <chrono>
#include <thread>

#if SERVER != 1
  #include "rice/Hash.hpp"
  #include "rice/String.hpp"
#endif

class IMUSensor
{
    public:
        /** \brief Initializes a new instance of a sensor interface.
          */
        IMUSensor();
        ~IMUSensor();

        void setLoggingStatus(bool);
        bool isLogging();

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

#if SERVER != 1
        /** \brief Returns a ruby hash containing all three coordinates aquired from HMC5883L's tri-axis data.
          *        Result in ruby: ["X"=>x, "Y"=>y, "Z"=>z]; They can be accessed as follows: puts var["X"]
          */
    	Rice::Object readCompass();
#endif

        /** \brief Returns the X-axis reading from the HMC5883L sensor.
          */
    	int32_t readCompassX();

        /** \brief Returns the Y-axis reading from the HMC5883L sensor.
          */
    	int32_t readCompassY();

        /** \brief Returns the Z-axis reading from the HMC5883L sensor.
          */
    	int32_t readCompassZ();

#if SERVER != 1
        /** \brief Returns a ruby hash containing all three coordinates aquired from MPU6050's Accelerometer.
          *        Result in ruby: ["X"=>x, "Y"=>y, "Z"=>z]; They can be accessed as follows: puts var["X"]
          */
    	Rice::Object readAccelerometer();
#endif

        /** \brief Returns the X-axis reading from the MPU6050's accelerometer.
          */
    	int32_t readAccelX();

        /** \brief Returns the Y-axis reading from the MPU6050's accelerometer.
          */
    	int32_t readAccelY();

        /** \brief Returns the Z-axis reading from the MPU6050's accelerometer.
          */
    	int32_t readAccelZ();

#if SERVER != 1
        /** \brief Returns a ruby hash containing all three coordinates aquired from MPU6050's Gyroscope.
          *        Result in ruby: ["X"=>x, "Y"=>y, "Z"=>z]; They can be accessed as follows: puts var["X"]
          */
    	Rice::Object readGyroscope();
#endif

        /** \brief Returns the X-axis reading from the MPU6050's gyroscope.
          */
    	int32_t readGyroX();

        /** \brief Returns the Y-axis reading from the MPU6050's gyroscope.
          */
    	int32_t readGyroY();

        /** \brief Returns the Z-axis reading from the MPU6050's gyroscope.
          */
    	int32_t readGyroZ();

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
        void launchLoggingThread();

        static int instanceCount_;
        std::shared_ptr<BMP085> sensorBMP085_;
        std::shared_ptr<HMC5883L> sensorHMC5883L_;
        std::shared_ptr<MPU6050> sensorMPU6050_;
        std::mutex sensorMutex_;
        bool loggingEnabled_;
};

#endif
