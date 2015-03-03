#!/bin/bash

# set up node.js server
sudo apt-get install nodejs npm
#sudo ln -s /usr/bin/nodejs /usr/bin/node

# install dependencies
cd webtcp
npm install
