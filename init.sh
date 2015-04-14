#!/bin/bash

init_version () {
    version=$(uname -r)
    if [[ $version == 3.8* ]]; then
        echo "Setting up environment for $version"
        # multiplex pins for pwm subsystems
        echo bone_pwm_P9_21 >> $SLOTS # Subsystem 0
        echo bone_pwm_P9_22 >> $SLOTS
        echo bone_pwm_P8_13 >> $SLOTS # Subsystem 2
        echo bone_pwm_P8_19 >> $SLOTS
        echo bone_pwm_P8_34 >> $SLOTS # Subsystem 1
        echo bone_pwm_P8_36 >> $SLOTS
        echo am33xx_pwm >> $SLOTS
        # turn on the ESCs by default
        i2cset -y 1 0x03 0x02 0x00

    elif [[ $version == 3.14* ]]; then
        echo "Setting up environment for $version"
        # multiplex pins for pwm subsystems
        config-pin P9.21 pwm # Subsystem 0
        config-pin P9.22 pwm
        config-pin P8.13 pwm # Subsystem 2
        config-pin P8.19 pwm
        config-pin P8.34 pwm # Subsystem 1
        config-pin P8.36 pwm
        # turn on the ESCs by default
        i2cset -y 2 0x03 0x02 0xE7
        
    else
        echo "Unsupported Version $version"
    fi
}


init_version
