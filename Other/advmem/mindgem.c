/**
  * Base code provided by
  * - SolidusCode: youtube.com
  * - Anil Kumar Pugalia : opensourceforu.com
  *
  * Created: Apr 12, 2015
  *      by: TekuConcept
  *
  *
  * Requirements: apt-get install linux-headers-$(uname -r)
  * Load with 'insmod <name>.ko'
  * Remove with 'rmmod <name>.ko'
  *
  */

#include <linux/module.h>   //
#include <linux/kernel.h>   //
#include <linux/init.h>     // initializations macros

#include <linux/fs.h>       // file_operations structure
#include <linux/cdev.h>     // char driver - cdev
#include <linux/device.h>   //
#include <linux/errno.h>    //
#include <asm/uaccess.h>    // copy_to_user; copy_from_user

#include <asm/io.h>         // ioremap, iounmap
#include "mindgem.h"

#define DEVICE_NAME "mindgem"
dev_t dev;                  // will hold major number that the kernel gives us
struct cdev c_dev;          // our character device
struct class *cl;

int major_number;           // will store our major number extracted from dev_t
int ret;                    // will be used to hold return values of functions
uint32_t* imem;             // mapped memory for ioctl control



/* ------------------------------------------------------------------ *\
|                          FILE OPERATIONS                             |
\* ------------------------------------------------------------------ */

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	query_arg_t q;

	switch(cmd) {
	case MINDGEM_READ:
		// read configuration from user
		if (copy_from_user(&q, (query_arg_t *)arg, sizeof(query_arg_t)))
		{
			return -EACCES;
		}

		// get value from register
		imem = ioremap(q.address, 0xFFF);
		if(imem != 0)
		{
			q.value = imem[q.offset/4];
			iounmap(imem);
		}

		// return value
		if (copy_to_user((query_arg_t *)arg, &q, sizeof(query_arg_t)))
		{
			return -EACCES;
		}
		break;

	case MINDGEM_WRITE:
		// read configuration from user
		if (copy_from_user(&q, (query_arg_t *)arg, sizeof(query_arg_t)))
		{
			return -EACCES;
		}

		// write to register
		imem = ioremap(q.address, 0xFFF);
		if(imem != 0)
		{
			imem[q.offset/4] = q.value;
			iounmap(imem);
		}
		break;

	default:
		return -EINVAL;
	}
	return 0;
}

int device_open(struct inode* inode, struct file* filp)
{
	printk(KERN_INFO "mindgem: opened device\n");
	return 0;
}

// user closes the file
int device_close(struct inode* inode, struct file* filp)
{
	printk(KERN_INFO "mindgem: closed device\n");
	return 0;
}

struct file_operations fops = {
	.owner   = THIS_MODULE,        // prevent unloading of this module when operations are in use
	.open    = device_open,        // points to the method to call when opening the device
	.release = device_close,       // points to the method to call when closing the device
	.unlocked_ioctl = device_ioctl // points to the method to call when executing a control command
};





/* ------------------------------------------------------------------ *\
|                              MAIN MODULE                             |
\* ------------------------------------------------------------------ */

static int __init driver_entry(void)
{
	struct device *dev_ret;
	printk(KERN_INFO "Initializing mindgem...\t");

	if((ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME)) < 0)
	{
		printk(KERN_ALERT "mindgem: failed to allocate major number\n");
		return ret;
	}

	cdev_init(&c_dev, &fops);

	if((ret = cdev_add(&c_dev, dev, 1)) < 0)
	{
		printk(KERN_ALERT "mindgem: unable to add cdev to kernel\n");
		return ret;
	}

	if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
	{
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, 1);
		return PTR_ERR(cl);
	}
	if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, DEVICE_NAME)))
	{
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, 1);
		return PTR_ERR(dev_ret);
	}

	printk(KERN_INFO "Done!\n");
	return 0;
}

static void __exit driver_exit(void)
{
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, 1);
	printk(KERN_ALERT "mindgem: unloaded module\n");
}



module_init(driver_entry);
module_exit(driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TekuConcept");
MODULE_DESCRIPTION("Exposes privledged physical memory to user space.");