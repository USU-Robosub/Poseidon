
# extconf file specific to the BeagleBone Black
require 'rubygems'
require 'mkmf-rice'

# compiler flags
$CFLAGS << " -std=c++0x -O3 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-deprecated"

create_makefile('DiveMaster')
