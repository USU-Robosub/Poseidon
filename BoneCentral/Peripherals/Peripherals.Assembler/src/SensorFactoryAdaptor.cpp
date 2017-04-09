//
// Created by Nathan Copier on 4/20/2016.
//

#include "SensorFactoryAdaptor.h"

SensorFactoryAdaptor::SensorFactoryAdaptor(I2CFactory& i2CFactory, SerialFactory& serialFactory) :
        i2CFactory_(i2CFactory), serialFactory_(serialFactory) { }

std::shared_ptr<IAccelerometer> SensorFactoryAdaptor::createAccelerometer() {
    return i2CFactory_.createAccelerometer();
}

std::shared_ptr<IGyroscope> SensorFactoryAdaptor::createGyroscope() {
    return i2CFactory_.createGyroscope();
}

std::shared_ptr<ICompass> SensorFactoryAdaptor::createCompass() {
    return i2CFactory_.createCompass();
}

std::shared_ptr<ITemperatureSensor> SensorFactoryAdaptor::createExternalTemperatureSensor() {
    return serialFactory_.createWaterTemperatureSensor();
}

std::shared_ptr<ITemperatureSensor> SensorFactoryAdaptor::createInternalTemperatureSensor1() {
    return i2CFactory_.createInternalTemperatureSensor1();
}

std::shared_ptr<ITemperatureSensor> SensorFactoryAdaptor::createInternalTemperatureSensor2() {
    return i2CFactory_.createInternalTemperatureSensor2();
}

std::shared_ptr<IPressureSensor> SensorFactoryAdaptor::createExternalPressureSensor() {
    return serialFactory_.createWaterPressureSensor();
}

std::shared_ptr<IPressureSensor> SensorFactoryAdaptor::createInternalPressureSensor() {
    return i2CFactory_.createInternalPressureSensor();
}
