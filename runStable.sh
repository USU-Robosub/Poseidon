#!/bin/bash

cd kernel
./compile.sh
cd ..

sudo ruby stable.rb