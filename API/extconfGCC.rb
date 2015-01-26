require 'mkmf-rice'

$CXXFLAGS += " -O3 --std=c++11 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations"

create_makefile('APIWrapper')
