/*
 * Registry.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: TekuConcept
 */

#include "Registry.h"


Registry::Registry(uint _addr_):
    addr(_addr_)
{}


unsigned int Registry::read(uint off)
{
    int val = 0;
    int mem_fd = open("/dev/mem", O_RDWR);
    if (mem_fd < 0)
        printf("Failed to open /dev/mem (%s)\n", strerror(errno));

    unsigned long* ddrMem = (unsigned long *)mmap(0, 0x0000FFFF, PROT_WRITE | PROT_READ, MAP_SHARED, mem_fd, addr);
    if (ddrMem == NULL)
    {
        printf("Failed to map the device (%s)\n", strerror(errno));
        close(mem_fd);
    }

    val = ddrMem[off/4];

    munmap(ddrMem, 0x0000FFFF);
    close(mem_fd);

    return val; // read  mode
}



void Registry::write(uint off, uint val)
{
    int mem_fd = open("/dev/mem", O_RDWR);
    if (mem_fd < 0)
        printf("Failed to open /dev/mem (%s)\n", strerror(errno));

    unsigned long* ddrMem = (unsigned long *)mmap(0, 0x0000FFFF, PROT_WRITE | PROT_READ, MAP_SHARED, mem_fd, addr);
    if (ddrMem == NULL)
    {
        printf("Failed to map the device (%s)\n", strerror(errno));
        close(mem_fd);
    }

    ddrMem[off/4] = val; // write mode

    munmap(ddrMem, 0x0000FFFF);
    close(mem_fd);
}



uint Registry::getAddr()
{
    return addr;
}
