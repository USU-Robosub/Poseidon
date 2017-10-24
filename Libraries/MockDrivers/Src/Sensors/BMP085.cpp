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
    ac4(0), ac5(0), ac6(0), oversampling(0) {}



BMP085::~BMP085() {}



int BMP085::WhoAmI() {
  return 0;
}



bool BMP085::initialize(uint8_t)
{
  return true;
}



int32_t BMP085::readPressure(void)
{
  return 0;
}



int32_t BMP085::readSealevelPressure(float)
{
  return 0;
}



float BMP085::readTemperature(void)
{
  return 0;
}



float BMP085::readAltitude(float)
{
  return 0;
}



/******************************************************************************/
/*                              Private Functions                             */
/******************************************************************************/



uint16_t BMP085::endian16(uint16_t)
{
  return 0;
}



uint8_t BMP085::endian8(uint8_t)
{
  return 0;
}



int32_t BMP085::computeB5(int32_t)
{
  return 0;
}



uint16_t BMP085::readRawTemperature(void)
{
  return 0;
}



uint32_t BMP085::readRawPressure(void)
{
  return 0;
}
