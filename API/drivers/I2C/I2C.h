/*
 * I2C2.h
 *
 *  Created on: Jan 18, 2015
 *      Author: TekuConcept
 */

#ifndef I2C_H_
#define I2C_H_

#include "I2C_Const.h"
#include "../Registry.h"

class I2C
{
    public:
        I2C(uint lane);

        // read from slave register of device
        uint read(uint s_addr, uint s_reg);

        // write to slave register of device
        void write(uint s_addr, uint s_reg, uint s_val);

        // used to test bus availability (experimental)
        uint isBusBusy();

    private:
        void wait_IRQ(uint idx);
        void reset();

        Registry addr;  // slave address used in this i2c interface

};

#endif /* I2C_H_ */
