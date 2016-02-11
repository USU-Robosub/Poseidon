/*
 * BMP085.cpp
 *
 *  Created on: Jan 29, 2015
 * Last Edited: Feb  7, 2016
 *  Fork: https://github.com/adafruit/Adafruit-BMP085-Library
 */

#include "BMP085.h"

BMP085::BMP085():
    ac1(0), ac2(0), ac3(0), b1(0), b2(0), mb(0), mc(0), md(0),
    ac4(0), ac5(0), ac6(0), oversampling(0)
{}



BMP085::~BMP085()
{}



bool BMP085::initialize(uint8_t mode)
{
    //fprintf(stderr, "BMP085 Mode = %d\n", mode);

    if (mode > IMU_ENVIRONMENT_ULTRAHIGHRES)
        mode = IMU_ENVIRONMENT_ULTRAHIGHRES;
    oversampling = mode;

    uint8_t devtest = I2C::readByte(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_DEVICE);
    if (devtest != IMU_ENVIRONMENT_DEV_ID)
        return false;

    /* read calibration data */
    ac1 = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_AC1);
    ac2 = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_AC2);
    ac3 = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_AC3);
    ac4 = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_AC4);
    ac5 = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_AC5);
    ac6 = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_AC6);

    b1  = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_B1);
    b2  = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_B2);

    mb  = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_MB);
    mc  = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_MC);
    md  = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CAL_MD);

    return true;
}



int32_t BMP085::readPressure(void)
{
    int32_t UT, UP, B3, B5, B6, X1, X2, X3, p;
    uint32_t B4, B7;

    UT = readRawTemperature();
    UP = readRawPressure();
    B5 = computeB5(UT);

    // do pressure calcs
    B6 = B5 - 4000;
    X1 = ((int32_t)b2 * ( (B6 * B6)>>12 )) >> 11;
    X2 = ((int32_t)ac2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = ((((int32_t)ac1*4 + X3) << oversampling) + 2) / 4;
    X1 = ((int32_t)ac3 * B6) >> 13;
    X2 = ((int32_t)b1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = ((uint32_t)ac4 * (uint32_t)(X3 + 32768)) >> 15;
    B7 = ((uint32_t)UP - B3) * (uint32_t)( 50000UL >> oversampling );

    if (B7 < 0x80000000)
        p = (B7 * 2) / B4;
    else
        p = (B7 / B4) * 2;

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;

    p = p + ((X1 + X2 + (int32_t)3791)>>4);

    return p;
}



int32_t BMP085::readSealevelPressure(float altitude_meters)
{
    float pressure = readPressure();
    float conversion = pow(1.0f - altitude_meters / 44330.0f, 5.255f);
    return (int32_t)(pressure / conversion);
}



float BMP085::readTemperature(void)
{
    int32_t UT, B5;     // following ds convention
    float temp = 0;

    UT = readRawTemperature();
    B5 = computeB5(UT);

    temp = (B5 + 8) / 16.0f;
    temp /= 10.0F;

    return temp;
}



float BMP085::readAltitude(float sealevelPressure)
{
    float pressure = readPressure();
    double altitude = 44330 * (1.0 - pow(pressure /sealevelPressure, 0.1903));

    return static_cast<float>(altitude);
}



/*********************************************************************/
/*                         Private Functions                         */
/*********************************************************************/



uint16_t BMP085::endian16(uint16_t x)
{
    uint16_t f = 0;
    for(int i = 0; i < 16; i++)
        f |= (((x >> i) & 1) << (15 - i)) | (((x >> (15 - i)) & 1) << i);

    return f;
}



uint8_t BMP085::endian8(uint8_t x)
{
    uint8_t f = 0;
    for(int i = 0; i < 8; i++)
        f |= (((x >> i) & 1) << (7 - i))|(((x >> (7 - i)) & 1) << i);

    return f;
}



int32_t BMP085::computeB5(int32_t UT)
{
    int32_t X1 = (UT - (int32_t)ac6) * ((int32_t)ac5) >> 15;
    int32_t X2 = ((int32_t)mc << 11) / (X1 + (int32_t)md);
    int32_t out = X1 + X2;
    
    return out;
}



uint16_t BMP085::readRawTemperature(void)
{
    I2C::writeByte(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CONTROL, IMU_ENVIRONMENT_TEMPERATURE);
    delay(5);

    return I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_RESULT);
}



uint32_t BMP085::readRawPressure(void)
{
    uint32_t raw;

    I2C::writeByte(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_CONTROL, IMU_ENVIRONMENT_PRESSURE0 +
        static_cast<uint8_t>(oversampling << 6));

    switch (oversampling)
    {
        case IMU_ENVIRONMENT_ULTRALOWPOWER:
            delay(5);
            break;

        case IMU_ENVIRONMENT_STANDARD:
            delay(8);
            break;

        case IMU_ENVIRONMENT_HIGHRES:
            delay(14);
            break;

        default:
            delay(26);
    }

    raw = I2C::readShort(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_RESULT);

    raw <<= 8;
    raw |= I2C::readByte(IMU_ENVIRONMENT_ADDR, IMU_ENVIRONMENT_RESULT+2);
    raw >>= (8 - oversampling);
    
    return raw;
}

