#!/bin/bash

#remove .o, Makefiles, and .so
find . -name "*.o" -type f -delete
rm -f Makefile
rm -f *.so

echo "Successfully cleaned the build environment"

