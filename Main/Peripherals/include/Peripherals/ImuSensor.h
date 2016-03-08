#ifndef IMU_CONTROLLER
#define IMU_CONTROLLER

#include "IAccelerometer.h"
#include "ICompass.h"
#include "IPressureSensor.h"
#include "IImuFactory.h"
#include "ILogger.h"

#include <memory>
#include <utility>
#include <string>

typedef std::tuple<float, float, float> FloatTuple;

class ImuSensor {
public:
    ImuSensor(IImuFactory& imuFactory, std::shared_ptr<ILogger> logger);
    FloatTuple getAcceleration();
    FloatTuple getHeading();
    int getPressure();
    // float getTemperature();
    ~ImuSensor();

private:
    std::shared_ptr<IAccelerometer> accelerometer_;
    std::shared_ptr<ICompass> compass_;
    std::shared_ptr<IPressureSensor> pressureSensor_;

    std::shared_ptr<ILogger> logger_;
};


#endif
