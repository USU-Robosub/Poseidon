#!/bin/bash

ruby extconfClang.rb

./fixMakefile.sh

cpus=$(grep -c ^processor /proc/cpuinfo)
make -j $cpus
