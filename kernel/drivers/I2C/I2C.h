/**
  * \class I2C
  *
  *  Created on: Jan 18, 2015
  *      Author: TekuConcept
  *
  * \brief This is a kernel wrapper for the I2C interface on a Linux system.
  *        It provides simple read and write functions for accessing generic I2C slaves.
  */

#ifndef I2C_H_
#define I2C_H_

#include "I2C_Const.h"
#include "../Registry.h"
#include "../Environment.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

class I2C
{
    public:
        /** \brief Initializes a new instance of an I2C software interface.
          * \param lane This is the specific hardware address of the bus to which commands will be applied.
          *             The address can be found in I2C_Const
          */
        I2C(uint lane);

        // read from slave device
        /** \brief Reads from a slave device on the bus.
          *        This is useful for when slave's do not use registers (like the Arduino UNO),
          *        or when a value needs to be re-read from the same register (only for supported devices).
          * \param s_addr The known address of the slave device.
          * \return Returns the byte returned by the slave as an unsigned integer.
          */
        uint readByte(uint s_addr);

        // read from slave register of device
        /** \brief Reads from a slave device's register.
          * \param s_addr The known address of the slave device.
          * \param s_reg The known register to read from.
          * \return Returns the byte returned by the slave as an unsigned integer.
          */
        uint readByte(uint s_addr, uint s_reg);

        // write to slave register of device
        /** \brief Writes to a slave devices's register.
          * \param s_addr The known address of the slave device.
          * \param s_reg The known register to which data will be written.
          * \param s_val A given unsigned value that will be written to the specified register.
          */
        void writeByte(uint s_addr, uint s_reg, uint s_val);

        // used to test bus availability (experimental)
        /** \brief This is an experimental method which doesn't currently have any real functionality. 
          * \return Returns wether the I2C bus is currently in use by the system or slave.
          */
        uint isBusBusy();

    private:
        int addr;
        //Registry addr;  // slave address used in this i2c interface

};

#endif /* I2C_H_ */
