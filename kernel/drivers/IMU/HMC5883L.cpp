/*
 * HMC5883L.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: TekuConcept
 */

#include "HMC5883L.h"


HMC5883L::HMC5883L(uint _bus_) :
    bus(_bus_), samples(Sx1), outRate(Hz15), gain(G1_3), mode(Single)
{}



HMC5883L::~HMC5883L()
{}



uint16_t HMC5883L::X()
{
    uint16_t v = bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_X_H) << 8;
    v |= bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_X_L);

    return v;
}



uint16_t HMC5883L::Y()
{
    uint16_t v = bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_Y_H) << 8;
    v |= bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_Y_L);
    return v;
}



uint16_t HMC5883L::Z()
{
    uint16_t v = bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_Z_H) << 8;
    v |= bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_Z_L);
    return v;
}



bool HMC5883L::isLocked()
{
    return (bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_STATUS) & 2) >> 1;
}



bool HMC5883L::isReady()
{
    return (bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_STATUS) & 1);
}



void HMC5883L::setSampleAverage(Sample ma)
{
    if (ma < 0 || ma > 3)
        throw std::invalid_argument("number of samples exceeds the maximum");

    samples = ma;

    uint cra = bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0x9F;
    cra |= ma << 5;
    bus.writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setOutputRate(Rate dor)
{
    if (dor < 0 || dor > 6)
        throw std::invalid_argument("output rate exceeds the maximum or is a reserved value");

    outRate = dor;

    uint cra = bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A) & 0xE3;
    cra |= dor << 2;
    bus.writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_A, cra);
}



void HMC5883L::setGain(Gain gn)
{
    if (gn < 0 || gn > 7)
        throw std::invalid_argument("gain exceeds the maximum");

    gain = gn;

    uint crb = bus.readByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B) & 0x1F;
    crb |= gn << 5;
    bus.writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_CONFIG_B, crb);
}



void HMC5883L::setMode(Mode md)
{
    if (md < 0 || md > 3)
        throw std::invalid_argument("specific mode does not exist");

    mode = md;

    bus.writeByte(IMU_COMPASS_ADDR, IMU_COMPASS_MODE, md);
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
