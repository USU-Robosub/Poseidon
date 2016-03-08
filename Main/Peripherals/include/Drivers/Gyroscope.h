#include "MPU6050.h"
#include "IGyroscope.h"

#include <memory>
#include <utility>

typedef std::tuple<float, float, float> FloatTuple
class Gyroscope : public IGyroscope {
public:
    Gyroscope(std::shared_ptr<MPU6050> gyroscope);
    FloatTuple getHeading();
    void setMagnitude(MPU6050::FS_SEL magnitudeOption);
private:
    std::shared_ptr<MPU6050> gyroscope_;
};
