/*
 * BMP085.cpp
 *
 *  Created on: Jan 29, 2015
 *  Fork: https://github.com/adafruit/Adafruit-BMP085-Library
 */

#include "Drivers/IMU/BMP085.h"

#define BMP085_DEBUG 0
#define delay(time) std::this_thread::sleep_for(std::chrono::milliseconds(time));


BMP085::BMP085(uint _bus_):
    bus(_bus_), ac1(0), ac2(0), ac3(0), b1(0), b2(0), mb(0), mc(0), md(0),
    ac4(0), ac5(0), ac6(0), oversampling(0)
{}



BMP085::~BMP085()
{}

void BMP085::print_debug() {
    fprintf(stderr, "ac1 = %d\n", ac1);
    fprintf(stderr, "ac2 = %d\n", ac2);
    fprintf(stderr, "ac3 = %d\n", ac3);
    fprintf(stderr, "ac4 = %d\n", ac4);
    fprintf(stderr, "ac5 = %d\n", ac5);
    fprintf(stderr, "ac6 = %d\n", ac6);

    fprintf(stderr, "b1 = %d\n", b1);
    fprintf(stderr, "b2 = %d\n", b2);

    fprintf(stderr, "mb = %d\n", mb);
    fprintf(stderr, "mc = %d\n", mc);
    fprintf(stderr, "md = %d\n", md);
}

bool BMP085::initialize(uint8_t mode)
{
    //fprintf(stderr, "BMP085 Mode = %d\n", mode);

    if (mode > IMU_ENVIRONMENT_ULTRAHIGHRES)
        mode = IMU_ENVIRONMENT_ULTRAHIGHRES;
    oversampling = mode;

    uint8_t devtest = read8(0xD0);
    if (devtest != 0x55)
        return false;

    /* read calibration data */
    ac1 = read16(IMU_ENVIRONMENT_CAL_AC1);
    //fprintf(stderr, "%X\n", ac1);
    ac2 = read16(IMU_ENVIRONMENT_CAL_AC2);
    ac3 = read16(IMU_ENVIRONMENT_CAL_AC3);
    ac4 = read16(IMU_ENVIRONMENT_CAL_AC4);
    ac5 = read16(IMU_ENVIRONMENT_CAL_AC5);
    ac6 = read16(IMU_ENVIRONMENT_CAL_AC6);

    b1 = read16(IMU_ENVIRONMENT_CAL_B1);
    b2 = read16(IMU_ENVIRONMENT_CAL_B2);

    mb = read16(IMU_ENVIRONMENT_CAL_MB);
    mc = read16(IMU_ENVIRONMENT_CAL_MC);
    md = read16(IMU_ENVIRONMENT_CAL_MD);

#if BMP085_DEBUG == 1
    fprintf(stderr, "First:\n");
    print_debug();
#endif

    return true;
}



int32_t BMP085::computeB5(int32_t UT)
{
    int32_t X1 = (UT - (int32_t)ac6) * ((int32_t)ac5) >> 15;
    int32_t X2 = ((int32_t)mc << 11) / (X1 + (int32_t)md);
    int32_t out = X1 + X2;
    //fprintf(stderr, "out = %d\nEnd\n", out);
    return out;
}



uint16_t BMP085::readRawTemperature(void)
{
    write8(IMU_ENVIRONMENT_CONTROL, IMU_ENVIRONMENT_TEMPERATURE);
    delay(5);

#if BMP085_DEBUG == 1
    fprintf(stderr, "Raw temp: %d\n", read16(IMU_ENVIRONMENT_RESULT));
#endif

    return read16(IMU_ENVIRONMENT_RESULT);
}



uint32_t BMP085::readRawPressure(void)
{
    uint32_t raw;

    write8(IMU_ENVIRONMENT_CONTROL, IMU_ENVIRONMENT_PRESSURE0 +
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

    raw = read16(IMU_ENVIRONMENT_RESULT);

    raw <<= 8;
    raw |= read8(IMU_ENVIRONMENT_RESULT+2);
    raw >>= (8 - oversampling);

    /* this pull broke stuff, look at it later?
    if (oversampling==0) {
    raw <<= 8;
    raw |= read8(BMP085_PRESSUREDATA+2);
    raw >>= (8 - oversampling);
    }
    */

#if BMP085_DEBUG == 1
    fprintf(stderr, "Raw pressure: %d\n", raw);
#endif
    return raw;
}



int32_t BMP085::readPressure(void)
{
    int32_t UT, UP, B3, B5, B6, X1, X2, X3, p;
    uint32_t B4, B7;

    UT = readRawTemperature();
    UP = readRawPressure();

#if BMP085_DEBUG == 1
    // use datasheet numbers!
    UT = 27898;
    UP = 23843;
    ac6 = 23153;
    ac5 = 32757;
    mc = -8711;
    md = 2868;
    b1 = 6190;
    b2 = 4;
    ac3 = -14383;
    ac2 = -72;
    ac1 = 408;
    ac4 = 32741;
    oversampling = 0;
    // initialize the following
    X1 = 0;
    X2 = 0;
#endif

    B5 = computeB5(UT);

#if BMP085_DEBUG == 1
    fprintf(stderr, "X1 = %d\n", X1);
    fprintf(stderr, "X2 = %d\n", X2);
    fprintf(stderr, "B5 = %d\n", B5);
#endif

    // do pressure calcs
    B6 = B5 - 4000;
    X1 = ((int32_t)b2 * ( (B6 * B6)>>12 )) >> 11;
    X2 = ((int32_t)ac2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = ((((int32_t)ac1*4 + X3) << oversampling) + 2) / 4;

#if BMP085_DEBUG == 1
    fprintf(stderr, "B6 = %d\n", B6);
    fprintf(stderr, "X1 = %d\n", X1);
    fprintf(stderr, "X2 = %d\n", X2);
    fprintf(stderr, "B3 = %d\n", B3);
#endif

    X1 = ((int32_t)ac3 * B6) >> 13;
    X2 = ((int32_t)b1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = ((uint32_t)ac4 * (uint32_t)(X3 + 32768)) >> 15;
    B7 = ((uint32_t)UP - B3) * (uint32_t)( 50000UL >> oversampling );

#if BMP085_DEBUG == 1
    fprintf(stderr, "X1 = %d\n", X1);
    fprintf(stderr, "X2 = %d\n", X2);
    fprintf(stderr, "B4 = %d\n", B4);
    fprintf(stderr, "B7 = %d\n", B7);
#endif

    if (B7 < 0x80000000)
        p = (B7 * 2) / B4;
    else
        p = (B7 / B4) * 2;

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;

#if BMP085_DEBUG == 1
    fprintf(stderr, "p = %d\n", p);
    fprintf(stderr, "X1 = %d\n", X1);
    fprintf(stderr, "X2 = %d\n", X2);
#endif

    p = p + ((X1 + X2 + (int32_t)3791)>>4);

#if BMP085_DEBUG == 1
    fprintf(stderr, "p = %d\n", p);
#endif

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
    //fprintf(stderr, "First:\n");
    //print_debug();

    int32_t UT, B5;     // following ds convention
    float temp = 0;

    UT = readRawTemperature();
    
#if BMP085_DEBUG == 1
    // use datasheet numbers!
    UT = 27898;
    ac6 = 23153;
    ac5 = 32757;
    mc = -8711;
    md = 2868;
#endif

    // fprintf(stderr, "UT = %d\n", UT);
    B5 = computeB5(UT);

     // fprintf(stderr, "B5 = %d\n", B5);
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

uint8_t BMP085::read8(uint8_t a)
{
    return bus.readByte(IMU_ENVIRONMENT_ADDR, a);
}



uint16_t BMP085::read16(uint8_t a)
{
    uint16_t ret;
    ret = static_cast<uint16_t>(bus.readByte(IMU_ENVIRONMENT_ADDR, a) << 8);
    ret |= bus.readByte(IMU_ENVIRONMENT_ADDR, a + 1);

    return ret;
}



void BMP085::write8(uint8_t a, uint8_t d)
{
    bus.writeByte(IMU_ENVIRONMENT_ADDR, a, d);
}



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

