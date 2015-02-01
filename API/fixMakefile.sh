#!/bin/bash

#gather .cpp files and generate their respective .o files
srcs=$(find . -name '*.cpp' | replace "./" "" | tr '\n' ' ')
objs=$(echo -n $srcs | replace ".cpp" ".o")

#insert this list into the Makefile
replace "DiveMaster.cpp" "$srcs" -- Makefile
replace "DiveMaster.o"   "$objs" -- Makefile
