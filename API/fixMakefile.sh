#!/bin/bash

#gather .cpp files and generate their respective .o files
srcs=$(find . -name '*.cpp' | replace "./" "" | tr '\n' ' ')
objs=$(echo -n $srcs | replace ".cpp" ".o")

#insert this list into the Makefile
awk '{gsub("DiveMaster.cpp", "'"$srcs"'"); print}' Makefile > tempMakefile
awk '{gsub("DiveMaster.o", "'"$objs"'"); print}' tempMakefile > Makefile
rm tempMakefile
