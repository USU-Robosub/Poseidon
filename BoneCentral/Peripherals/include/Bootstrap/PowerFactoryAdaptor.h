//
// Created by Nathan Copier on 4/20/2016.
//

#ifndef PERIPHERALS_POWER_FACTORY_ADAPTOR_H
#define PERIPHERALS_POWER_FACTORY_ADAPTOR_H

#include <IPowerFactory.h>
#include <I2CFactory.h>
#include "SerialFactory.h"

class PowerFactoryAdaptor : public IPowerFactory {
public:
    PowerFactoryAdaptor(I2CFactory& i2CFactory, SerialFactory& serialFactory);
    std::shared_ptr<IImuPower> createImuPower();
    std::shared_ptr<IEscPower> createEscPower();
private:
    I2CFactory& i2CFactory_;
    SerialFactory& serialFactory_;
};

#endif //PERIPHERALS_POWER_FACTORY_ADAPTOR_H
