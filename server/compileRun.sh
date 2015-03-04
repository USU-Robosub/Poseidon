#!/bin/sh

cmake .
cpus=$(grep -c ^processor /proc/cpuinfo)

#find . -name '*.cpp' | awk '{ gsub("^./",""); print}' > kernelCPPs.txt

if (make -j $cpus) then
    sudo netstat -ap | grep 4322
    sudo ./RCServer
fi
