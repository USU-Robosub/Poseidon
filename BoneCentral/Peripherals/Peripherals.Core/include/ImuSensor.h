#ifndef IMU_CONTROLLER
#define IMU_CONTROLLER

#include "ISensorFactory.h"
#include "ILogger.h"

#include <memory>
#include <utility>
#include <string>
#include <sstream>
#include <tuple>

typedef std::tuple<float, float, float> FloatTuple;

class ImuSensor {
public:
    ImuSensor(ISensorFactory& sensorFactory, std::shared_ptr<ILogger> logger);
    FloatTuple getAcceleration();
    FloatTuple getAngularAcceleration(); // gyroscope
    FloatTuple getHeading();
    int getExtPressure();
    int getIntPressure();
    float getExtTemperature();
    float getIntTemperature(); // sensor fusion
    ~ImuSensor();

private:
    std::shared_ptr<IAccelerometer> accelerometer_;
    std::shared_ptr<IGyroscope> gyroscope_;
    std::shared_ptr<ICompass> compass_;
    std::shared_ptr<IPressureSensor> extPressureSensor_;
    std::shared_ptr<IPressureSensor> intPressureSensor_;
    std::shared_ptr<ITemperatureSensor> extTemperatureSensor_;
    std::shared_ptr<ITemperatureSensor> intTemperatureSensor1_;
    std::shared_ptr<ITemperatureSensor> intTemperatureSensor2_;
    std::shared_ptr<ILogger> logger_;
};


#endif
