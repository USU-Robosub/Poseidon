#!/bin/bash

ruby extconfClang.rb
./fixMakefile.sh

cpus=$(grep -c ^processor /proc/cpuinfo)
if (! make -j $cpus)
then
    ./clean.sh #compilation failed, don't allow Ruby to hook into it
fi
