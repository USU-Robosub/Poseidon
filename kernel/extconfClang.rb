
# extconf file specific to the BeagleBone Black
require 'rubygems'
require 'mkmf-rice'

$CXX = "/usr/bin/clang++"
$CC = "/usr/bin/clang"

$CXXFLAGS += " -O3 --std=c++0x -Wno-c++98-compat-pedantic -pedantic -Weverything -Wno-old-style-cast -Wno-sign-conversion -Wno-disabled-macro-expansion -Wno-documentation -Wno-deprecated -Wno-global-constructors -Wno-exit-time-destructors -Wno-weak-vtables -Wno-padded -Wno-cast-align -Wno-zero-length-array"

create_makefile('DiveMaster')
