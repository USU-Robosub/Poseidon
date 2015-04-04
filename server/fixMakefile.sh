#!/bin/bash

#gather .cpp files and generate their respective .o files
srcs=$(find . -name '*.cpp' | awk '{ gsub("^./",""); print}' | tr '\n' ' ')
objs=$(echo -n $srcs | awk '{ gsub(".cpp",".o"); print}')

#insert this list into the Makefile
awk '{gsub("RCServer.cpp main.cpp", "'"$srcs"'"); print}' Makefile > tempMakefile
awk '{gsub("RCServer.o main.o", "'"$objs"'"); print}' tempMakefile > Makefile
rm tempMakefile
