
#include <IGyroscope.h>
#include <tuple>

class MockGyroscope : public IGyroscope {
public:
    std::tuple<float, float, float> getAngularAcceleration()
    {
        return make_tuple(0, 0, 0);
    }
    void setMagnitude(int magnitudeOption) {}
};
