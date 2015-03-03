#!/bin/bash

cpus=$(grep -c ^processor /proc/cpuinfo)
if (! gcc Server.cpp -o Server)
then
    ./clean.sh #compilation failed, don't allow Ruby to hook into it
fi
