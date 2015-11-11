#include "IMUSensor.h"

IMUSensor::IMUSensor()
{

    std::cout << "Initializing IMUSensor..." << std::endl;

    //create and initialize IMU BMP085 (pressure/temp) module
    std::cout << "Setting up BMP085 chip..." << std::endl;
    sensorBMP085_ = std::make_shared<BMP085>(I2C_SUB2);
    sensorBMP085_->initialize(1);

    //create and initialize IMU HMC5883L (compass) module
    std::cout << "Setting up HMC5883L chip..." << std::endl;
    sensorHMC5883L_ = std::make_shared<HMC5883L>(I2C_SUB2);
    sensorHMC5883L_->setSampleAverage(HMC5883L::Sample::Sx4);
    sensorHMC5883L_->setOutputRate(HMC5883L::Rate::Hz75);
    //sensorHMC5883L_->setGain(HMC5883L::Gain::G8_1);
    sensorHMC5883L_->setMode(HMC5883L::Mode::Single);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //create and initialize IMU MPU6050 (gyro) module
    std::cout << "Setting up MPU6050 chip..." << std::endl;
    sensorMPU6050_ = std::make_shared<MPU6050>(I2C_SUB2);
}



IMUSensor::~IMUSensor()
{
    std::cout << "Tearing down IMUSensor..." << std::endl;
}


float IMUSensor::readTemperature()
{
    sensorMutex_.lock();
    auto r = sensorBMP085_->readTemperature();
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readPressure()
{
    sensorMutex_.lock();
    auto r = sensorBMP085_->readPressure();
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readSealevel(float altitudeMeters)
{
    sensorMutex_.lock();
    auto r = sensorBMP085_->readSealevelPressure(altitudeMeters);
    sensorMutex_.unlock();

    return r;
}



float IMUSensor::readAltitude(float sealevelPressure)
{
    sensorMutex_.lock();
    auto r = sensorBMP085_->readAltitude(sealevelPressure);
    sensorMutex_.unlock();

    return r;
}


int32_t IMUSensor::readCompassX()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorHMC5883L_->X());
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readCompassY()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorHMC5883L_->Y());
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readCompassZ()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorHMC5883L_->Z());
    sensorMutex_.unlock();

    return r;
}


int32_t IMUSensor::readAccelX()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorMPU6050_->accel_X());
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readAccelY()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorMPU6050_->accel_Y());
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readAccelZ()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorMPU6050_->accel_Z());
    sensorMutex_.unlock();

    return r;
}

int32_t IMUSensor::readGyroX()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorMPU6050_->gyro_X());
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readGyroY()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorMPU6050_->gyro_Y());
    sensorMutex_.unlock();

    return r;
}



int32_t IMUSensor::readGyroZ()
{
    sensorMutex_.lock();
	auto r = static_cast<int32_t>(sensorMPU6050_->gyro_Z());
    sensorMutex_.unlock();

    return r;
}



float IMUSensor::getTemp()
{
    sensorMutex_.lock();
    auto r = sensorMPU6050_->temp();
    sensorMutex_.unlock();

    return r;
}



void IMUSensor::turnOn()
{
    sensorMutex_.lock();
    sensorMPU6050_->awake();
    sensorMutex_.unlock();
}



void IMUSensor::turnOff()
{
    sensorMutex_.lock();
    sensorMPU6050_->sleep();
    sensorMutex_.unlock();
}
