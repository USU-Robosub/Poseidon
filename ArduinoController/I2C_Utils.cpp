#include "I2C_Utils.h"

uint8_t I2C_Utils::readByte(uint8_t device, uint8_t addr)
{
    Wire.beginTransmission(device);
    Wire.write(byte(addr));
    Wire.endTransmission();
    Wire.requestFrom(device, byte(1));

    return static_cast<uint8_t>(Wire.read());
}



uint16_t I2C_Utils::readShort(uint8_t device, uint8_t addr)
{
    Wire.beginTransmission(device);
    Wire.write(byte(addr));
    Wire.endTransmission();
    Wire.requestFrom(device, byte(2));

    return static_cast<uint16_t>(Wire.read()<<8 | Wire.read());
}



void I2C_Utils::writeByte(uint8_t device, uint8_t addr, uint8_t data)
{
    Wire.beginTransmission(device);
    Wire.write(byte(addr));
    Wire.write(byte(data));
    Wire.endTransmission();
}

