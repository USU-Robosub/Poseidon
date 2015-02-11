/*
 * I2C2.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: TekuConcept
 */

#include <chrono>
#include <thread>
#include <iostream>
#include <bitset>
#include "I2C.h"

// ------   PUBLIC      ------


I2C::I2C(uint lane):
    addr(lane)
{}



uint I2C::read(uint s_addr, uint s_reg)
{
    reset();
    addr.write(I2C_SA  , s_addr); // slave address
    addr.write(I2C_CNT , 0x0001); // write 1 byte
    // send slave register address
    addr.write(I2C_DATA, s_reg);

    // -----------------------------------------------------------
    // [-- Begin write sequence --]
    addr.write(I2C_CON , 0x8601); // enable i2c
                                  // set as master-transmitter
                                  // send START command

    // wait for XRDY command
    // wait_IRQ(4);

    // wait for ARDY command
    wait_IRQ(2); // - CAUTION -

    // send STOP command
    addr.write(I2C_CON, 0x8602);

    // reset interrupts for clean read sequence testing
    addr.write(I2C_IRQSTATUS, addr.read(I2C_IRQSTATUS_RAW));
    // -----------------------------------------------------------



    // -----------------------------------------------------------
    // [-- Begin read sequence --]
    addr.write(I2C_CON, 0x8403); // set as master-receiver
                                 // send START and STOP commands

    // wait for RRDY command
    wait_IRQ(3);

    // read one byte
    uint res = addr.read(I2C_DATA);

    // wait for ARDY command
    wait_IRQ(2); // - CAUTION -

    // -----------------------------------------------------------

    return res;
}



void I2C::write(uint s_addr, uint s_reg, uint s_val)
{
    reset();
    addr.write(I2C_SA  , s_addr); // slave address (0xAC)
    addr.write(I2C_CNT , 0x02); // write 2 byte  (0x98)

    // send slave register address
    addr.write(I2C_DATA, s_reg);  // (0x9C)
    // send slave register value
    addr.write(I2C_DATA, s_val);  // (0x9C)

    // FIFO is requesting more than it should
    // if((addr.read(I2C_BUFSTAT)&0x3F) > 0) return 0;

    // -----------------------------------------------------------
    // [-- Begin write sequence --]
    addr.write(I2C_CON , 0x8601); // enable i2c    (0xA4)
                                  // set as master-transmitter
                                  // send START command

    // wait for ARDY command
    //success = wait_IRQ(2);      // CAUTION: ARDY not guaranteed

    // send STOP command
    addr.write(I2C_CON, 0x8602);  // (0xA4)
    // -----------------------------------------------------------
}



uint I2C::isBusBusy()
{
    std::bitset<32> bits(addr.read(I2C_IRQSTATUS_RAW));
    return bits.test(12);
}



// ------   PRIVATE     ------

void I2C::reset()
{
    // remove interrupt flags
    uint irq = addr.read(I2C_IRQENABLE_SET); // (0x2C)
    addr.write(I2C_IRQENABLE_CLR, irq);     // (0x30)

    // [-- Set system settings --]
    // (Reset and Set procedures are needed to prevent fatal operating system crashes
    // or even worse, system corruption requiring a fresh OS reinstall - use at
    // your own risk & backup any and all files as necessary)
    //addr.write(I2C_PSC , 0x000B); // something magical happens (0xB0)
    //addr.write(I2C_SCLL, 0x000D); // SCL low time              (0xB4)
    //addr.write(I2C_SCLH, 0x000F); // SCL high time             (0xB8)
    //addr.write(I2C_WE  , 0x636F); // wait enable               (0x34)
    //addr.write(I2C_SYSC, 0x001D); // re-enable internal clock  (0x10)

    // reset interrupts
    addr.write(I2C_IRQSTATUS, addr.read(I2C_IRQSTATUS_RAW));// (R0x24 W0x28)
}



void I2C::wait_IRQ(uint idx)
{
    uint var = addr.read(I2C_IRQSTATUS_RAW);
    std::bitset<32> bits(var);

    while (!bits.test(idx))
    {
        var = addr.read(I2C_IRQSTATUS_RAW);

        std::bitset<32> temp(var);
        bits = temp;
    }

    // clear IQR status flags
    addr.write(I2C_IRQSTATUS, var);
}
