//
// Created by Nathan Copier on 4/20/2016.
//

#include "PowerFactoryAdaptor.h"

PowerFactoryAdaptor::PowerFactoryAdaptor(I2CFactory& i2CFactory, SerialFactory& serialFactory) :
        i2CFactory_(i2CFactory),
        serialFactory_(serialFactory) { }

std::shared_ptr<IImuPower> PowerFactoryAdaptor::createImuPower() {
    return i2CFactory_.createImuPower();
}

std::shared_ptr<IEscPower> PowerFactoryAdaptor::createEscPower() {
    return serialFactory_.createEscPower();
}

