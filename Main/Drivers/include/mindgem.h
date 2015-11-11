#ifndef MINDGEM_IOCTL_H
#define MINDGEM_IOCTL_H

#include <sys/ioctl.h>

typedef struct
{
    uint32_t address;
    uint16_t offset;
    uint32_t value;
} query_arg_t;

#define MINDGEM_READ _LINUX_IOWR('q', 1, query_arg_t *)
#define MINDGEM_WRITE _LINUX_IOW('q', 2, query_arg_t *)

#endif