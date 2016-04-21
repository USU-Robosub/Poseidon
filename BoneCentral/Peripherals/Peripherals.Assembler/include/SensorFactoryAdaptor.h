//
// Created by Nathan Copier on 4/20/2016.
//

#ifndef PERIPHERALS_SENSOR_FACTORY_H
#define PERIPHERALS_SENSOR_FACTORY_H

#include <ISensorFactory.h>
#include <I2CFactory.h>
#include <SerialFactory.h>

class SensorFactoryAdaptor : public ISensorFactory {
public:
    SensorFactoryAdaptor(I2CFactory& i2CFactory, SerialFactory& serialFactory);
    virtual std::shared_ptr<IAccelerometer> createAccelerometer();
    virtual std::shared_ptr<IGyroscope> createGyroscope();
    virtual std::shared_ptr<ICompass> createCompass();
    virtual std::shared_ptr<ITemperatureSensor> createExternalTemperatureSensor();
    virtual std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor1();
    virtual std::shared_ptr<ITemperatureSensor> createInternalTemperatureSensor2();
    virtual std::shared_ptr<IPressureSensor> createExternalPressureSensor();
    virtual std::shared_ptr<IPressureSensor> createInternalPressureSensor();
private:
    I2CFactory& i2CFactory_;
    SerialFactory& serialFactory_;
};


#endif //PERIPHERALS_SENSOR_FACTORY_H
