#!/bin/bash

ruby extconfGCC.rb

#no way to tell Ruby this, so this applies sources by find-replace
oldSrcs="APIWrapper.cpp"
srcs="APIWrapper.cpp API/ThrustController.cpp API/IMUSensor.cpp drivers/I2C.cpp drivers/PWM.cpp drivers/Registry.cpp"
replace "$oldSrcs" "$srcs" -- Makefile

#no way to tell Ruby this, so this lists objects to link together
oldObjs="APIWrapper.o"
objs="APIWrapper.o API/ThrustController.o API/IMUSensor.o drivers/I2C.o drivers/PWM.o drivers/Registry.o"
replace "$oldObjs" "$objs" -- Makefile

cpus=$(grep -c ^processor /proc/cpuinfo)
make -j $cpus
