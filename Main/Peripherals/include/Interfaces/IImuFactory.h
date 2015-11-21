//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_IMU_FACTORY_H
#define PERIPHERALS_I_IMU_FACTORY_H

#include "IPressureSensor.h"
#include "ICompass.h"
#include "IAccelerometer.h"

class IImuFactory {
public:
    virtual std::shared_ptr<IPressureSensor> createPressureSensor() = 0;
    virtual std::shared_ptr<ICompass> createCompass() = 0;
    virtual std::shared_ptr<IAccelerometer> createAccelerometer() = 0;
};

#endif //PERIPHERALS_I_IMU_FACTORY_H
