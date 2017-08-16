#include "I2C.h"

// read 1 byte from slave device
uint8_t I2C::readByte(uint8_t, uint8_t, uint8_t) {
  return 0;
}

// read 2 bytes from slave device
uint16_t I2C::readShort(uint8_t, uint8_t, uint8_t) {
  return 0;
}

// read n-number of bytes from device
void I2C::burstRead(uint8_t, uint8_t, uint8_t*, uint8_t, uint8_t) {

}

// write to slave register of device
void I2C::writeByte(uint8_t, uint8_t, uint8_t, uint8_t) {

}

// helper function
int I2C::getDevFileHandle(uint8_t, uint8_t) {
	  return 0;
}
