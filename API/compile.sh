#!/bin/bash

ruby extconf.rb

# Is the script running on a Beaglebone Black
if `echo $(cat /proc/cpuinfo | grep name) | grep -i "${ARM}" 1>/dev/null 2>&1`
then
	echo "Finished"
else
	./fixMakefile.sh
fi

cpus=$(grep -c ^processor /proc/cpuinfo)
if (! make -j $cpus)
then
    ./clean.sh #compilation failed, don't allow Ruby to hook into it
fi
