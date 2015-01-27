#!/bin/bash

if [ ! -f API/APIWrapper.so ]; then
    cd API
    ./compile.sh
    cd ..
fi

sudo ruby main.rb
