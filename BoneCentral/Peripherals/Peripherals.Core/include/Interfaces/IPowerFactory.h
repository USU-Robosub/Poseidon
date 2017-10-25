//
// Created by Nathan Copier on 4/20/2016.
//

#ifndef PERIPHERALS_I_POWER_FACTORY_H
#define PERIPHERALS_I_POWER_FACTORY_H

#include <memory>
#include "IImuPower.h"
#include "IEscPower.h"

class IPowerFactory {
public:
    virtual std::shared_ptr<IImuPower> createImuPower() = 0;
    virtual std::shared_ptr<IEscPower> createEscPower() = 0;
};

#endif //PERIPHERALS_I_POWER_FACTORY_H
