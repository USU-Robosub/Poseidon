#ifndef DRIVERS_COMPASS_H
#define DRIVERS_COMPASS_H

#include "HMC5883L.h"
#include "ICompass.h"

#include <memory>
#include <utility>
#include <tuple>

typedef std::tuple<float, float, float> FloatTuple;

class Compass : public ICompass {
public:
    Compass(std::shared_ptr<HMC5883L> compass);
    FloatTuple getHeading();
private:
    std::shared_ptr<HMC5883L> compass_;
};

#endif