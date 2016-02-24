/*
 * HMC5883L.cpp
 *
 *  Created on: Jan 31, 2015
 * Last Edited: Feb  7, 2016
 *      Author: TekuConcept
 */

#include "HMC5883L.h"


HMC5883L::HMC5883L() {}



HMC5883L::~HMC5883L() {}



short HMC5883L::X() {
    return I2C::readShort(IMU_COMPASS_ADDR, IMU_COMPASS_X_H);
}



short HMC5883L::Y() {
    return I2C::readShort(IMU_COMPASS_ADDR, IMU_COMPASS_Y_H);
}



short HMC5883L::Z() {
    return I2C::readShort(IMU_COMPASS_ADDR, IMU_COMPASS_Z_H);
}



bool HMC5883L::isLocked() {
    return (I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_STATUS) & 2) >> 1;
}



bool HMC5883L::isReady() {
    return (I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_STATUS) & 1);
}



void HMC5883L::setSampleAverage(Sample ma) {
    uint cra = I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0x9F;
    cra |= static_cast<int>(ma) << 5;
    I2C::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setOutputRate(Rate dor) {

    uint cra = I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0xE3;
    cra |= static_cast<int>(dor) << 2;
    I2C::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setGain(Gain gn) {
    uint crb = I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B) & 0x1F;
    crb |= static_cast<int>(gn) << 5;
    I2C::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B, crb);
}



void HMC5883L::setMode(Mode md) {
    int _m_ = static_cast<int>(md);
    I2C::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_MODE, _m_);
}



int HMC5883L::getSampleAverage() {
    return ((I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0x60) >> 5);
}



int HMC5883L::getOutputRate() {
    return ((I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0x1C) >> 2);
}



int HMC5883L::getGain() {
    return ((I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B) & 0xE0) >> 5);
}



int HMC5883L::getMode() {
    return ((I2C::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_MODE) & 0x03));
}
