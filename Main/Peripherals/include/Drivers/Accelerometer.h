#include "MPU6050.h"
#include "IAccelerometer.h"

#include <memory>
#include <utility>

typedef std::tuple<float, float, float> FloatTuple;

class Accelerometer : public IAccelerometer {
public:
    Accelerometer(std::shared_ptr<MPU6050> accelerometer);
    FloatTuple getAcceleration();
    void setMagnitude(MPU6050::AFS_SEL magnitudeOption);
private:
    std::shared_ptr<MPU6050> accelerometer_;
};
