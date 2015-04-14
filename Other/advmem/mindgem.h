#ifndef MINDGEM_IOCTL_H
#define MINDGEM_IOCTL_H

#include <linux/ioctl.h>

typedef struct
{
    uint32_t address;
    uint16_t offset;
    uint32_t value;
} query_arg_t;

#define MINDGEM_READ _IOWR('q', 1, query_arg_t *)
#define MINDGEM_WRITE _IOW('q', 2, query_arg_t *)

#endif