#!/bin/bash

ruby extconfGCC.rb

./fixMakefile.sh

cpus=$(grep -c ^processor /proc/cpuinfo)
make -j $cpus
