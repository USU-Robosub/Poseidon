#!/bin/bash

# remove broken device file descriptor
dev="/dev/ttyACM0"
if [ -e $dev ]; then rm /dev/ttyACM0; fi

# recreate device descriptor
echo -n "1-1:1.0" > /sys/bus/usb/drivers/cdc_acm/unbind
echo -n "1-1:1.0" > /sys/bus/usb/drivers/cdc_acm/bind

# rename device descriptor to original name
file=$(find /dev -name "ttyACM*" -print)
if [ "$file" != "$dev" ]; then mv $file $dev; fi