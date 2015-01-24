/*
 * Registry.h
 *
 *  Created on: Jan 18, 2015
 *      Author: TekuConcept
 */

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

class Registry
{
    public:
        // open a direct path to physical space
        Registry(uint _addr_);

        // read from a register within the address range
        // from off = 0x0000; to off = 0x0FFF;
        uint read(uint off);

        // write to a register within the address range
        // from off = 0x0000; to off = 0x0FFF;
        // with the given value
        void write(uint off, uint val);

        // returns the base address associated with this class object
        uint getAddr();

    private:
        uint addr;          // beginning address of register
        bool showRegWarning;

};

#endif /* REGISTRY_H_ */
