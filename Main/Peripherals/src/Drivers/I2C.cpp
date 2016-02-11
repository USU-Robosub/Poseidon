#include "I2C.h"

// read 1 byte from slave device
uint8_t I2C::readByte(uint8_t device, uint8_t reg, uint8_t i2c) {
	int _i2c_ = I2C::getDevFileHandle(i2c, device);
	if(_i2c_ < 0) return 0;

	i2c_smbus_write_byte(_i2c_, reg);
	uint8_t val = i2c_smbus_read_byte(_i2c_);
	close(_i2c_);

	return val;
}

// read 2 bytes from slave device
uint16_t I2C::readShort(uint8_t device, uint8_t reg, uint8_t i2c) {
	int _i2c_ = I2C::getDevFileHandle(i2c, device);
	if(_i2c_ < 0) {
		close(_i2c_);
		return 0;
	}
	
	//uint16_t val = i2c_smbus_read_word_data(_i2c_, reg);
	i2c_smbus_write_byte(_i2c_, reg);
	uint16_t val = i2c_smbus_read_byte(_i2c_) << 8;
	i2c_smbus_write_byte(_i2c_, reg+1);
	val |= i2c_smbus_read_byte(_i2c_);
	close(_i2c_);
	
	return val;
}

// read n-number of bytes from device
void I2C::burstRead(uint8_t device, uint8_t reg, uint8_t* buffer, uint8_t size, uint8_t i2c) {
	int _i2c_ = I2C::getDevFileHandle(i2c, device);
	if(_i2c_ < 0) {
		// fill buffer with null values ?
		close(_i2c_);
		return;
	}
	
	int cnt = i2c_smbus_read_block_data(_i2c_, reg, buffer);
	if(cnt != size)
		fprintf(stderr, "Bytes read into buffer is not equal to size\n");
	
	close(_i2c_);
}

// write to slave register of device
void I2C::writeByte(uint8_t device, uint8_t reg, uint8_t value, uint8_t i2c) {
	int _i2c_ = I2C::getDevFileHandle(i2c, device);

	char buf[10];
	buf[0] = reg;
	buf[1] = value;
	if(write(_i2c_, buf, 2) != 2)
		fprintf(stderr, "error writing to device");
	close(_i2c_);
}

// helper function
int I2C::getDevFileHandle(uint8_t i2c, uint8_t slave) {
	int handle;
            
    // open appropriate file descriptor
    switch(i2c) {
		case 0:
			handle = open("/dev/i2c-0", O_RDWR);
			break;
		case 1:
			handle = open("/dev/i2c-1", O_RDWR);
			break;
		case 2:
			handle = open("/dev/i2c-2", O_RDWR);
			break;
		default:
			fprintf(stderr, "File not found: %d", i2c);
		    return -1;
	}
	
	// set up handle with the given slave address
	if(ioctl(handle, I2C_SLAVE, slave) < 0)
	{
		fprintf(stderr, "An error occured while setting up the slave address\n");
		close(handle);
		return -2;
	}
	
	return handle;
}
