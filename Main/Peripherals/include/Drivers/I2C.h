/**
  * \class I2C
  *
  *   Created on: Jan 18, 2015
  *  Last Edited: Feb  7, 2016
  *       Author: TekuConcept
  *
  * \brief This is a kernel wrapper for the I2C interface on a Linux system.
  *        It provides simple read and write functions for accessing generic I2C slaves.
  */

#ifndef I2C_H_
#define I2C_H_

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

class I2C
{
    public:
        // read from slave register of device
        /** \brief Reads one byte from the slave device.
          * \param device The known address of the slave device.
          * \param reg The known register to read from.
          * \param i2c I2C device to perform the operation on; default: 1
          * \return Returns the byte returned by the slave as an unsigned integer.
          */
        static uint8_t readByte(uint8_t device, uint8_t reg, uint8_t i2c=2);
        
        // read from slave register of device
        /** \brief Reads two bytes from the slave device.
          * \param device The known address of the slave device.
          * \param reg The known register to read from.
          * \param i2c I2C device to perform the operation on; default: 1
          * \return Returns the byte returned by the slave as an unsigned integer.
          */
        static uint16_t readShort(uint8_t device, uint8_t reg, uint8_t i2c=2);

        // read from slave register of device
        /** \brief Reads a stream of bytes from the slave device in one call.
          * \param device The known address of the slave device.
          * \param reg The known register to read from.
          * \param buffer Array to store the values in.
          * \param size How many bytes to read in.
          * \param i2c I2C device to perform the operation on; default: 1
          */
        static void burstRead(uint8_t device, uint8_t reg, uint8_t* buffer, uint8_t size, uint8_t i2c=2);

        // write to slave register of device
        /** \brief Writes to a slave devices's register.
          * \param device The known address of the slave device.
          * \param reg The known register to which data will be written.
          * \param value A given unsigned value that will be written to the specified register.
          * \param i2c I2C device to perform the operation on; default: 1
          */
        static void writeByte(uint8_t device, uint8_t reg, uint8_t value, uint8_t i2c=2);
    
    private:
        /** \brief Helper function that returns a file descriptor to the i2c device.
         * 
         *  \param device I2C device to access.
         *  \param slave The slave device reads and writes are performed upon.
         *  \return Returns the file descriptor to the device.
         */
        static int getDevFileHandle(uint8_t i2c, uint8_t slave);
};

#endif /* I2C_H_ */
