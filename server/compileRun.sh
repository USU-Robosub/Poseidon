#!/bin/sh

cmake .
cpus=$(grep -c ^processor /proc/cpuinfo)

if (make -j $cpus) then
    netstat -ap | grep 4322
    ./RCServer
fi
