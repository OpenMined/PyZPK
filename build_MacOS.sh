#!/bin/bash

cd libsnark
mkdir build
cd build
#Initialization of libsnark
git submodule init
# Update libsnark in order to pull down the files.
git submodule update --init --recursive
# Reset all submodules
git submodule foreach --recursive git reset --hard

brew install cmake
brew install gmp        
brew install boost
brew install gcc
ln -s /usr/local/opt/openssl/include/openssl /usr/local/include
cmake -DWITH_PROCPS=OFF -DWITH_SUPERCOP=OFF ..


make
