/*
 * HMC5883L.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: TekuConcept
 */

#include "HMC5883L.h"


HMC5883L::HMC5883L() :
    samples(Sx1), outRate(Hz15), gain(G1_3), mode(Single)
{}



HMC5883L::~HMC5883L()
{}



uint16_t HMC5883L::X()
{
    uint16_t v = read16(IMU_COMPASS_X_H);

    return v;
}



uint16_t HMC5883L::Y()
{
    uint16_t v = read16(IMU_COMPASS_Y_H);
    return v;
}



uint16_t HMC5883L::Z()
{
    uint16_t v = read16(IMU_COMPASS_Z_H);
    return v;
}



bool HMC5883L::isLocked()
{
    return (readByte(IMU_COMPASS_STATUS) & 2) >> 1;
}



bool HMC5883L::isReady()
{
    return (readByte(IMU_COMPASS_STATUS) & 1);
}



void HMC5883L::setSampleAverage(Sample ma)
{
    if (ma < 0 || ma > 3)
        return;

    samples = ma;

    uint cra = readByte(IMU_COMPASS_CONFIG_A) & 0x9F;
    cra |= ma << 5;
    writeByte(IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setOutputRate(Rate dor)
{
    if (dor < 0 || dor > 6)
        return;

    outRate = dor;

    uint cra = readByte(IMU_COMPASS_CONFIG_A) & 0xE3;
    cra |= dor << 2;
    writeByte(IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setGain(Gain gn)
{
    if (gn < 0 || gn > 7)
        return;

    gain = gn;

    uint crb = readByte(IMU_COMPASS_CONFIG_B) & 0x1F;
    crb |= gn << 5;
    writeByte(IMU_COMPASS_CONFIG_B, crb);
}



void HMC5883L::setMode(Mode md)
{
    if (md < 0 || md > 3)
        return;

    mode = md;

    writeByte(IMU_COMPASS_MODE, md);
}



uint HMC5883L::getSampleAverage()
{
    return samples;
}



uint HMC5883L::getOutputRate()
{
    return outRate;
}



uint HMC5883L::getGain()
{
    return gain;
}



uint HMC5883L::getMode()
{
    return mode;
}

uint8_t HMC5883L::readByte(uint8_t addr)
{
    Wire.beginTransmission(IMU_COMPASS_ADDR);
    Wire.write(byte(addr));
    Wire.endTransmission();
    Wire.requestFrom(IMU_COMPASS_ADDR, 1);

    return static_cast<uint8_t>(Wire.read());
}

uint16_t HMC5883L::read16(uint8_t addr)
{
    Wire.beginTransmission(IMU_COMPASS_ADDR);
    Wire.write(byte(addr));
    Wire.endTransmission();
    Wire.requestFrom(IMU_COMPASS_ADDR, 2);

    return static_cast<uint16_t>(Wire.read()<<8 | Wire.read());
}

void HMC5883L::writeByte(uint8_t addr, uint8_t data)
{
    Wire.beginTransmission(IMU_COMPASS_ADDR);
    Wire.write(byte(addr));
    Wire.write(byte(data));
    Wire.endTransmission();
}

