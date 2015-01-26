require 'mkmf-rice'

$CXXFLAGS += " -O3 --std=c++11 -Wall -Wextra -Wdouble-promotion -Wfloat-equal -Wunsafe-loop-optimizations -Wno-unused-parameter"

create_makefile('ThrustControllerAPI')
