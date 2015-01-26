#!/bin/bash

ruby extconfGCC.rb

cpus=$(grep -c ^processor /proc/cpuinfo)
make -j $cpus
