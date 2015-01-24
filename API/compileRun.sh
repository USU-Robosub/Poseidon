#!/bin/sh
cmake .
cpus=$(grep -c ^processor /proc/cpuinfo)

if (make -j $cpus) then
    ./PoseidonAPI
fi
