
#ifndef IMU_SENSOR
#define IMU_SENSOR

#include "../drivers/IMU/BMP085.h"
#include "../drivers/IMU/HMC5883L.h"
#include "../drivers/IMU/MPU6050.h"
#include "../drivers/Vector3D.h"
#include <memory>

class IMUSensor
{
    public:
        IMUSensor();
        ~IMUSensor();

        float readInteriorTemperature();
        int32_t readPressure();
        int32_t readSealevelPressure(float altitudeMeters = 0);
        float readAltitude(float sealevelPressure = 101325);
        Vector3D readCompass();
        Vector3D getAcceleration();
        Vector3D getGyro();
        int16_t getTemp();

    private:
        static int instanceCount_;
        std::shared_ptr<BMP085> sensorBMP085_;
        std::shared_ptr<HMC5883L> sensorHMC5883L_;
        std::shared_ptr<MPU6050> sensorMPU6050_;
};

#endif
