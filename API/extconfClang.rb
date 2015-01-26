require 'mkmf-rice'

$CXX = "/usr/bin/clang++"
$CC = "/usr/bin/clang"

$CXXFLAGS += " -O3 --std=c++11 -Wno-c++98-compat-pedantic -pedantic -Weverything -Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-non-virtual-dtor -Wno-weak-vtables -Wno-padded -Wno-cast-align -Wno-gnu -Wno-nested-anon-types -Wno-documentation-unknown-command -Wno-unknown-pragmas"

create_makefile('ThrustControllerAPI')
