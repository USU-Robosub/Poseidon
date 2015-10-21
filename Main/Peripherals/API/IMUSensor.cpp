
#include "IMUSensor.h"
#include <fstream>
#include <iostream>


//list static members so I can reference them
int IMUSensor::instanceCount_;


IMUSensor::IMUSensor():
    loggingEnabled_(true)
{
    if (instanceCount_ >= 1)
        throw new std::runtime_error("Cannot have more than one IMUSensor!");

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

    //launchLoggingThread();
}



IMUSensor::~IMUSensor()
{
    std::cout << "Tearing down IMUSensor..." << std::endl;
    instanceCount_--;
}


/*
void IMUSensor::launchLoggingThread()
{
	fprintf(stderr, "logging thread...\n");
    std::thread t([&]() {
        //initialize constants
	fprintf(stderr, "initializing...\n");
        using namespace std::chrono;
        const auto STATUS_POLL = milliseconds(100);
        const auto LOG_SPEED = milliseconds(333);
        auto startTime = steady_clock::now(); //relative time till we have a clock

	fprintf(stderr, "creating log file...\n");
        //open file
        std::ofstream logFile;
        logFile.open("IMU.log", std::ofstream::out | std::ofstream::app);
        logFile << "------------------------------" << std::endl; //marker

	fprintf(stderr, "loop\n");
        while (true)
        {
            while (loggingEnabled_)
            {
		fprintf(stderr, "loggingEnabled_\n");
                std::this_thread::sleep_for(STATUS_POLL);
            }

            //get current time
		fprintf(stderr, "getting current time\n");
            auto now = steady_clock::now();
            auto elapsed = duration_cast<milliseconds>(now - startTime).count();

            //write variables
		fprintf(stderr, "writing variables to file\n");
            logFile << elapsed << " readTemperature: " << readTemperature() << std::endl;
            logFile << elapsed << " readPressure: " << readPressure() << std::endl;
            logFile << elapsed << " readSealevel: " << readSealevel() << std::endl;
            logFile << elapsed << " readAltitude: " << readAltitude() << std::endl;
            logFile << elapsed << " readCompassX: " << readCompassX() << std::endl;
            logFile << elapsed << " readCompassY: " << readCompassY() << std::endl;
            logFile << elapsed << " readCompassZ: " << readCompassZ() << std::endl;
            logFile << elapsed << " readAccelX: " << readAccelX() << std::endl;
            logFile << elapsed << " readAccelY: " << readAccelY() << std::endl;
            logFile << elapsed << " readAccelZ: " << readAccelZ() << std::endl;
            logFile << elapsed << " readGyroX: " << readGyroX() << std::endl;
            logFile << elapsed << " readGyroY: " << readGyroY() << std::endl;
            logFile << elapsed << " readGyroZ: " << readGyroZ() << std::endl;
            logFile << elapsed << " getTemp: " << getTemp() << std::endl;
            logFile.flush(); //write to file

            //pause for a bit
		fprintf(stderr, "pausing for a bit\n");
            std::this_thread::sleep_for(LOG_SPEED);
        }
    });

	fprintf(stderr, "end of func\n");
    //t.detach();
}



void IMUSensor::setLoggingStatus(bool enableLogging)
{
    loggingEnabled_ = enableLogging;
}



bool IMUSensor::isLogging()
{
    return loggingEnabled_;
}
*/


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


#if SERVER != 1
Rice::Object IMUSensor::readCompass()
{
    sensorMutex_.lock();

	Rice::String x("X");
	Rice::String y("Y");
	Rice::String z("Z");
	Rice::Hash h;
	h[x] = static_cast<int32_t>(sensorHMC5883L_->X());
	h[y] = static_cast<int32_t>(sensorHMC5883L_->Y());
	h[z] = static_cast<int32_t>(sensorHMC5883L_->Z());

    sensorMutex_.unlock();

	return h;
}
#endif


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


#if SERVER != 1
Rice::Object IMUSensor::readAccelerometer()
{
    sensorMutex_.lock();

	Rice::String x("X");
	Rice::String y("Y");
	Rice::String z("Z");
	Rice::Hash h;
	h[x] = static_cast<int32_t>(sensorMPU6050_->accel_X());
	h[y] = static_cast<int32_t>(sensorMPU6050_->accel_Y());
	h[z] = static_cast<int32_t>(sensorMPU6050_->accel_Z());

    sensorMutex_.unlock();
	return h;
}
#endif


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


#if SERVER != 1
Rice::Object IMUSensor::readGyroscope()
{
    sensorMutex_.lock();

	Rice::String x("X");
	Rice::String y("Y");
	Rice::String z("Z");
	Rice::Hash h;
	h[x] = static_cast<int32_t>(sensorMPU6050_->gyro_X());
	h[y] = static_cast<int32_t>(sensorMPU6050_->gyro_Y());
	h[z] = static_cast<int32_t>(sensorMPU6050_->gyro_Z());

    sensorMutex_.unlock();
	return h;
}
#endif


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
