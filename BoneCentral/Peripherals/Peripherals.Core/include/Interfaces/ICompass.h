//
// Created by Nathan Copier on 11/21/2015.
//

#ifndef PERIPHERALS_I_COMPASS_H
#define PERIPHERALS_I_COMPASS_H

#include "Vector.h"

class ICompass {
public:
    virtual Vector getHeading() = 0;
};

#endif //PERIPHERALS_I_COMPASS_H
