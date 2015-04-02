#include "I2C.h"

I2C::I2C(uint lane)
{
	switch(lane) {
		case I2C_SUB0:
			addr = open("/dev/i2c-0", O_RDWR);
			break;
		case I2C_SUB1:
#if KVERSION == 1
			addr = open("/dev/i2c-2", O_RDWR);
#elif KVERSION == 2
			addr = open("/dev/i2c-1", O_RDWR);
#else
#error "undefined version number for i2c"
#endif
			break;
		case I2C_SUB2:
#if KVERSION == 1
			addr = open("/dev/i2c-1", O_RDWR);
#elif KVERSION == 2
			addr = open("/dev/i2c-2", O_RDWR);
#else
#error "undefined version number for i2c"
#endif
			break;
		default:
			throw 1;
			break;
	}

	if(addr < 0)
	{
		printf("error setting bus - make sure the bus is enabled first\n");
	}
}

// read from slave device
uint I2C::readByte(uint s_addr) {
	if(ioctl(addr, I2C_SLAVE, s_addr) < 0)
	{
		printf("error setting up slave address\n");
		return 0;
	}

	return i2c_smbus_read_byte(addr);
}

// read from slave register of device
uint I2C::readByte(uint s_addr, uint s_reg) {
	if(ioctl(addr, I2C_SLAVE, s_addr) < 0)
	{
		printf("error setting up slave address\n");
		return 0;
	}

	i2c_smbus_write_byte(addr, s_reg);
	return i2c_smbus_read_byte(addr);;

	//return buf[0];
}

// write to slave register of device
void I2C::writeByte(uint s_addr, uint s_reg, uint s_val) {
	if(ioctl(addr, I2C_SLAVE, s_addr) < 0)
	{
		printf("error setting up slave address\n");
		return;
	}

	char buf[10];
	buf[0] = s_reg;
	buf[1] = s_val;
	if(write(addr, buf, 2) != 2) {
		printf("error writing to device");
		return;
	}
}

// used to test bus availability (experimental)
uint I2C::isBusBusy() {

	return 0;
}
