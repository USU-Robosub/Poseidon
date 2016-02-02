/*
 * HMC5883L.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: TekuConcept
 */

#include "HMC5883L.h"


HMC5883L::HMC5883L()
{}



HMC5883L::~HMC5883L()
{}



uint16_t HMC5883L::X()
{
    return I2C_Utils::readShort(IMU_COMPASS_ADDR, IMU_COMPASS_X_H);
}



uint16_t HMC5883L::Y()
{
    return I2C_Utils::readShort(IMU_COMPASS_ADDR, IMU_COMPASS_Y_H);
}



uint16_t HMC5883L::Z()
{
    return I2C_Utils::readShort(IMU_COMPASS_ADDR, IMU_COMPASS_Z_H);
}



bool HMC5883L::isLocked()
{
    return I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_STATUS) & 0x02;
}



bool HMC5883L::isReady()
{
    return I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_STATUS) & 0x01;
}



void HMC5883L::setSampleAverage(Sample ma)
{
    if (ma < 0 || ma > 3)
        return;

    uint cra = I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0x9F;
    cra |= ma << 5;
    I2C_Utils::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setOutputRate(Rate dor)
{
    if (dor < 0 || dor > 6)
        return;

    uint cra = I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0xE3;
    cra |= dor << 2;
    I2C_Utils::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setGain(Gain gn)
{
    if (gn < 0 || gn > 7)
        return;

    uint crb = I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B) & 0x1F;
    crb |= gn << 5;
    I2C_Utils::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B, crb);
}



void HMC5883L::setMode(Mode md)
{
    if (md < 0 || md > 3)
        return;

    I2C_Utils::writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_MODE, md);
}



uint HMC5883L::getSampleAverage()
{
    return I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0x6F;
}



uint HMC5883L::getOutputRate()
{
    return I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0x1C;
}



uint HMC5883L::getGain()
{
    return I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B) & 0xE0;
}



uint HMC5883L::getMode()
{
    return I2C_Utils::readByte(IMU_COMPASS_ADDR, IMU_COMPASS_MODE) & 0x03;
}

