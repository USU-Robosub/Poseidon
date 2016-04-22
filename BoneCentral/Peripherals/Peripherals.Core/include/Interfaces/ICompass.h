//
// Created by Nathan Copier on 11/21/2015.
//

#ifndef PERIPHERALS_I_COMPASS_H
#define PERIPHERALS_I_COMPASS_H

#include <tuple>

typedef std::tuple<float, float, float> FloatTuple;

class ICompass {
public:
    virtual FloatTuple getHeading() = 0;
};

#endif //PERIPHERALS_I_COMPASS_H
