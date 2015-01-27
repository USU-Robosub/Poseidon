#!/bin/bash

cd API
./compile.sh
cd ..

sudo ruby main.rb
