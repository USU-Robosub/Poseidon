/**
  * \class Registry
  *
  *  Created on: Jan 18, 2015
  *      Author: TekuConcept
  *
  * \brief This object provides direct access for physical space - a program can read from or write to physical hardware addresses in memory.
  */

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <string.h>

#include <../../../../MindGem/mindgem.h>
#define MEM_DEVICE "/dev/mindgem"

class Registry
{
    public:
        /** \brief Opens a direct path to memory in physical space.
          * \param addr An unsigned integer representing a specific address block of interest.
          */
        Registry(uint _addr_);
        ~Registry();

        /** \brief Reads from a register within the address block.
          * \param off An unsigned integer defining the sub-address to read from within the block.
          *            This value can range from 0x0000 to 0x0FFF.
          * \return An unsigned integer representing the value of the addressed register.
          */
        uint read(uint off);

        /** \brief Writes to a register within the address block.
          * \param off An unsigned integer defining the sub-address to write to within the block.
          *            This value can range from 0x0000 to 0x0FFF.
          * \param val An unsigned integer defining the value to be written to memory.
          *            This value can range from 0x00000000 to 0xFFFFFFFF
          */
        void write(uint off, uint val);

        /** \return The base address associated with this Registry object
          */
        uint getAddr();

    private:
        query_arg_t q;
        int fd;
        bool showRegWarning;

};

#endif /* REGISTRY_H_ */
