#!/bin/bash

# Updating libboost to run the cmake (requirement)
sudo apt-get install libboost-all-dev
# Updating libprocps to run the cmake (requirement)
sudo apt-get install libprocps-dev
sudo apt install make
sudo apt-get install python3-dev # for python.h file

rm -r third_party/libsnark
rm -r third_party/pybind11
#Sync & Initialization of libsnark
git submodule sync
git submodule init
# Update libsnark in order to pull down the files.
git submodule update --init --recursive
# Reset all submodules
git submodule foreach --recursive git reset --hard

sudo apt-get install build-essential cmake git libgmp3-dev python-markdown libssl-dev


