#!/bin/bash

# Updating libboost to run the cmake (requirement) 
sudo apt-get install libboost-all-dev
# Updating libprocps to run the cmake (requirement) 
sudo apt-get install libprocps-dev

rm -r libsnark
git submodule init
git submodule update --init --recursive

cd libsnark
mkdir build
cd build

cmake ..

make

