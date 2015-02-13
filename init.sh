#!/bin/bash

#SLOTS=/sys/devices/bone_capemgr.*/slots
source ~/.bashrc

# mux and initialize PWM pins
echo bone_pwm_P9_21 >> $SLOTS # Subsystem 0
echo bone_pwm_P9_22 >> $SLOTS
echo bone_pwm_P8_13 >> $SLOTS # Subsystem 2
echo bone_pwm_P8_19 >> $SLOTS
echo bone_pwm_P8_34 >> $SLOTS # Subsystem 1
echo bone_pwm_P8_36 >> $SLOTS
echo am33xx_pwm >> $SLOTS



# Enable i2c_Sub2 clock
writem 0x44E00000  0 0
writem 0x44E00000 44 2
