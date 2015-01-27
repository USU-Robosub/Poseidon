require 'mkmf-rice'

$CXXFLAGS += " -O3 --std=c++0x -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations"

create_makefile('DiveMaster')
