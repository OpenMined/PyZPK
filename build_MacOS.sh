#!/bin/bash

cd libsnark
mkdir build
cd build
git submodule update --init --recursive

brew install cmake
brew install gmp        
brew install boost
brew install gcc
ln -s /usr/local/opt/openssl/include/openssl /usr/local/include
cmake -DWITH_PROCPS=OFF -DWITH_SUPERCOP=OFF ..


make
