//
// Created by Nathan Copier on 11/21/2015.
//

#include "ImuFactory.h"

std::shared_ptr<IPressureSensor> ImuFactory::createPressureSensor() {
    return std::make_shared<BMP085>(I2C_SUB2);
}


std::shared_ptr<ICompass> ImuFactory::createCompass() {
    auto compass = std::make_shared<HMC5883L>(I2C_SUB2);
    compass->setSampleAverage(HMC5883L::Sample::Sx4);
    compass->setOutputRate(HMC5883L::Rate::Hz75);
    //sensorHMC5883L_->setGain(HMC5883L::Gain::G8_1);
    compass->setMode(HMC5883L::Mode::Single);
    return compass;
}

std::shared_ptr<IAccelerometer> ImuFactory::createAccelerometer() {
    return std::make_shared<MPU6050>(I2C_SUB2);
}
