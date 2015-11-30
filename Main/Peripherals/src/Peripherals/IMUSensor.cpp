#include "IMUSensor.h"

IMUSensor::IMUSensor(IImuFactory& imuFactory, std::shared_ptr<ILogger> logger) :
        pressureSensor_(imuFactory.createPressureSensor()),
        compass_(imuFactory.createCompass()),
        accelerometer_(imuFactory.createAccelerometer()),
        logger_(logger)
{

    logger_->info("Initializing IMUSensor...");

    //create and initialize IMU BMP085 (pressure/temp) module
    logger_->info("Setting up BMP085 chip...");
    pressureSensor_->initialize(1);

    //create and initialize IMU HMC5883L (compass) module
    logger_->info("Setting up HMC5883L chip...");

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //create and initialize IMU MPU6050 (gyro) module
    logger_->info("Setting up MPU6050 chip...");
}



IMUSensor::~IMUSensor()
{
    logger_->info("Tearing down IMUSensor...");
}


float IMUSensor::readTemperature()
{
    sensorMutex_.lock();
    auto r = pressureSensor_->readTemperature();
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readPressure()
{
    sensorMutex_.lock();
    auto r = pressureSensor_->readPressure();
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readSealevel(float altitudeMeters)
{
    sensorMutex_.lock();
    auto r = pressureSensor_->readSealevelPressure(altitudeMeters);
    sensorMutex_.unlock();

    return r;
}



float IMUSensor::readAltitude(float sealevelPressure)
{
    sensorMutex_.lock();
    auto r = pressureSensor_->readAltitude(sealevelPressure);
    sensorMutex_.unlock();

    return r;
}


int16_t IMUSensor::readCompassX()
{
    sensorMutex_.lock();
	auto r = compass_->X();
    sensorMutex_.unlock();

    return r;
}



int16_t IMUSensor::readCompassY()
{
    sensorMutex_.lock();
	auto r = compass_->Y();
    sensorMutex_.unlock();

    return r;
}



int16_t IMUSensor::readCompassZ()
{
    sensorMutex_.lock();
	auto r = compass_->Z();
    sensorMutex_.unlock();

    return r;
}


int16_t IMUSensor::readAccelX()
{
    sensorMutex_.lock();
	auto r = accelerometer_->accel_X();
    sensorMutex_.unlock();

    return r;
}



int16_t IMUSensor::readAccelY()
{
    sensorMutex_.lock();
	auto r = accelerometer_->accel_Y();
    sensorMutex_.unlock();

    return r;
}



int16_t IMUSensor::readAccelZ()
{
    sensorMutex_.lock();
	auto r = accelerometer_->accel_Z();
    sensorMutex_.unlock();

    return r;
}

int16_t IMUSensor::readGyroX()
{
    sensorMutex_.lock();
	auto r = accelerometer_->gyro_X();
    sensorMutex_.unlock();

    return r;
}



int16_t IMUSensor::readGyroY()
{
    sensorMutex_.lock();
	auto r = accelerometer_->gyro_Y();
    sensorMutex_.unlock();

    return r;
}



int16_t IMUSensor::readGyroZ()
{
    sensorMutex_.lock();
	auto r = accelerometer_->gyro_Z();
    sensorMutex_.unlock();

    return r;
}



float IMUSensor::getTemp()
{
    sensorMutex_.lock();
    auto r = accelerometer_->temp();
    sensorMutex_.unlock();

    return r;
}



void IMUSensor::turnOn()
{
    sensorMutex_.lock();
    accelerometer_->awake();
    sensorMutex_.unlock();
}



void IMUSensor::turnOff()
{
    sensorMutex_.lock();
    accelerometer_->sleep();
    sensorMutex_.unlock();
}
