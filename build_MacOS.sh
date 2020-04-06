#!/bin/bash

#installing Dependencies
brew list cmake || brew install cmake
brew list gmp || brew install gmp
brew list boost || brew install boost
brew list gcc || brew install gcc
brew list pkg-config || brew install pkg-config

# Removing old directory
rm -rf third_party/libsnark
rm -rf third_party/pybind11

#Sync & Initialization of libsnark
git submodule sync
git submodule intit

# Update libsnark in order to pull down the files.
 git submodule update --init --recursive
# Reset all submodules
git submodule foreach --recursive git reset --hard

cd third_party/libsnark
mkdir build
cd build

#Exporting Flags
LD_LIBRARY_PATH=/usr/local/opt/openssl/lib:"${LD_LIBRARY_PATH}"
CPATH=/usr/local/opt/openssl/include:"${CPATH}"
PKG_CONFIG_PATH=/usr/local/opt/openssl/lib/pkgconfig:"${PKG_CONFIG_PATH}"
export LD_LIBRARY_PATH CPATH PKG_CONFIG_PATH

CPPFLAGS=-I/usr/local/opt/openssl/include
LDFLAGS=-L/usr/local/opt/openssl/lib
PKG_CONFIG_PATH=/usr/local/opt/openssl/lib/pkgconfig
cmake -DWITH_PROCPS=OFF -DWITH_SUPERCOP=OFF ..


make

cd ../../..
mkdir build
cd build

cmake ..

make