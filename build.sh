#!/bin/bash

# Updating libboost to run the cmake (requirement)
sudo apt-get install libboost-all-dev
# Updating libprocps to run the cmake (requirement)
sudo apt-get install libprocps-dev

rm -r third_party/libsnark
rm -r third_party/pybind11
#Sync & Initialization of libsnark
git submodule sync
git submodule init
# Update libsnark in order to pull down the files.
git submodule update --init --recursive
# Reset all submodules
git submodule foreach --recursive git reset --hard


cd third_party/libsnark
mkdir build
cd build

cmake ..

make

cd ../../..
mkdir build
cd build

cmake ..

make