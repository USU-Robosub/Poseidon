#!/bin/bash

ruby extconfClang.rb

cpus=$(grep -c ^processor /proc/cpuinfo)
make -j $cpus
