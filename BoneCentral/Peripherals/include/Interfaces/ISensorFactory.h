//
// Created by Nathan Copier on 11/20/2015.
//

#ifndef PERIPHERALS_I_SENSOR_FACTORY_H
#define PERIPHERALS_I_SENSOR_FACTORY_H

#include <memory>
#include "IAccelerometer.h"
#include "IGyroscope.h"
#include "ICompass.h"
#include "ITemperatureSensor.h"
#include "IPressureSensor.h"
#include "IImuPower.h"
#include "IEscPower.h"

class ISensorFactory {
public:
    virtual std::shared_ptr<IAccelerometer> createAccelerometer() = 0;
    virtual std::shared_ptr<IGyroscope> createGyroscope() = 0;
	virtual std::shared_ptr<ICompass> createCompass() = 0;
	virtual std::shared_ptr<ITemperatureSensor> createExternalTemperatureSensor() = 0;
	virtual std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor1() = 0;
	virtual std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor2() = 0;
    virtual std::shared_ptr<IPressureSensor> createExternalPressureSensor() = 0;
    virtual std::shared_ptr<IPressureSensor> createInternalPressureSensor() = 0;
};

#endif //PERIPHERALS_I_IMU_FACTORY_H
