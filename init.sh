#!/bin/bash

source ~/.bashrc
#source kernel/kernel.sh


# -- Kernel v3.8 --
echo bone_pwm_P9_21 >> $SLOTS # Subsystem 0
echo bone_pwm_P9_22 >> $SLOTS
echo bone_pwm_P8_13 >> $SLOTS # Subsystem 2
echo bone_pwm_P8_19 >> $SLOTS
echo bone_pwm_P8_34 >> $SLOTS # Subsystem 1
echo bone_pwm_P8_36 >> $SLOTS
echo am33xx_pwm >> $SLOTS

i2cset -y 1 0x03 0x02 0x00
# -- End --


# -- Kernel v3.14 --
#echo pwm > /sys/devices/ocp.3/P9_21_pinmux.48/state # Subsystem 0
#echo pwm > /sys/devices/ocp.3/P9_22_pinmux.49/state
#echo pwm > /sys/devices/ocp.3/P8_13_pinmux.10/state # Subsystem 2
#echo pwm > /sys/devices/ocp.3/P8_19_pinmux.16/state
#echo pwm > /sys/devices/ocp.3/P8_34_pinmux.25/state # Subsystem 1
#echo pwm > /sys/devices/ocp.3/P8_36_pinmux.27/state

#writem 0x44E00000  0 0 # Wakeup CM_PER_L4LS_CLKSTCTRL.CLKTRCTRL = 0
#writem 0x44E00000 D4 2 # Enable CM_PER_EPWMSS0_CLKCTRL.MODULEMODE = 2
#writem 0x44E00000 CC 2 # Enable CM_PER_EPWMSS1_CLKCTRL.MODULEMODE = 2
#writem 0x44E00000 D8 2 # Enable CM_PER_EPWMSS2_CLKCTRL.MODULEMODE = 2

#i2cset -y 2 0x03 0x02 0xE7
# -- End --


# Enable i2c_Sub2 clock
#writem 0x44E00000  0 0
#writem 0x44E00000 44 2
#i2cset -y 2 0x03 0x02 0xE7
