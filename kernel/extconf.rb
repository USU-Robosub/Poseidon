require 'rubygems'
require 'mkmf-rice'

# compiler flags
$CFLAGS << " -std=c++0x -O3 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-deprecated"

# linker flags
# $LFLAGS << " -lmath" # link libmath.so

# make Makefile
create_makefile('DiveMaster')
