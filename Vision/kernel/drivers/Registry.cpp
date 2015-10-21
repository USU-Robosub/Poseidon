/*
 * Registry.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: TekuConcept
 */

#include "Registry.h"
#include <climits>


Registry::Registry(uint _addr_):
    showRegWarning(true)
{
    if((fd = open(MEM_DEVICE, O_RDWR | O_NONBLOCK)) < 0)
    {
        fprintf(stderr, "File %s either does not exist or is rendered inaccessable at this time.\n", MEM_DEVICE);
        throw -1;
    }

    q.address = _addr_;
    q.offset  = 0x0000;
    q.value   = 0x00000000;
}



Registry::~Registry()
{
    if(!(fd < 0))
        close(fd);
}



uint Registry::read(uint off)
{
    q.offset = off;
    q.value  = 0x00000000;
    if(ioctl(fd, MINDGEM_READ, &q))
    {
        throw -2;
    }
    else
    {
        return q.value;
    }
}



void Registry::write(uint off, uint val)
{
    q.offset = off;
    q.value  = val;
    if(ioctl(fd, MINDGEM_WRITE, &q))
    {
        throw -2;
    }
}



uint Registry::getAddr()
{
    return q.address;
}
