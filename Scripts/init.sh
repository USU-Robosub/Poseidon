#!/bin/bash

# multiplex pins for pwm subsystems
config-pin P9.21 pwm # Subsystem 0
config-pin P9.22 pwm
config-pin P8.13 pwm # Subsystem 2
config-pin P8.19 pwm
config-pin P8.34 pwm # Subsystem 1
config-pin P8.36 pwm
# turn on the ESCs by default
i2cset -y 2 0x03 0x02 0xE7

if [[ $(lsmod | grep mindgem) != mindgem* ]]; then
  cd ../Main/MindGem
  make install
fi


init_version
