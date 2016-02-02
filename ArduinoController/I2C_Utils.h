#ifndef I2C_UTILS_H_
#define I2C_UTILS_H_

#include <Wire.h>
#include "stdint.h"

class I2C_Utils
{
    public:
        static uint8_t readByte(uint8_t device, uint8_t addr);
        static uint16_t readShort(uint8_t device, uint8_t addr);
        static void writeByte(uint8_t device, uint8_t addr, uint8_t data);
};

#endif
