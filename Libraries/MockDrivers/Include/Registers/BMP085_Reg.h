/**
  * \class BMP085
  *
  *  Created on: March 6, 2016
  *      Author: TekuConcept
  *
  * \brief A comprehensive list of slave register addresses.
  */

#ifndef BMP085_REG_H_
#define BMP085_REG_H_

// --- BMP085 --- https://www.sparkfun.com/datasheets/Components/General/BST-BMP085-DS000-05.pdf
#define BMP085_ADDR        0x77 //
#define BMP085_TEMPERATURE 0x2E //
#define BMP085_PRESSURE0   0x34 //
#define BMP085_PRESSURE1   0x74 //
#define BMP085_PRESSURE2   0xB4 //
#define BMP085_PRESSURE3   0xF4 //
#define BMP085_CONTROL     0xF4 //
#define BMP085_RESULT      0xF6 //
#define BMP085_CAL_AC1     0xAA // r
#define BMP085_CAL_AC2     0xAC // r
#define BMP085_CAL_AC3     0xAE // r
#define BMP085_CAL_AC4     0xB0 // r
#define BMP085_CAL_AC5     0xB2 // r
#define BMP085_CAL_AC6     0xB4 // r
#define BMP085_CAL_B1      0xB6 // r
#define BMP085_CAL_B2      0xB8 // r
#define BMP085_CAL_MB      0xBA // r
#define BMP085_CAL_MC      0xBC // r
#define BMP085_CAL_MD      0xBE // r
#define BMP085_DEVICE      0xD0 // r
#define BMP085_DEV_ID      0x55 //
#define BMP085_ULTRALOWPOWER 0
#define BMP085_STANDARD      1
#define BMP085_HIGHRES       2
#define BMP085_ULTRAHIGHRES  3

#endif