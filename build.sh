#!/bin/bash

cd libsnark
mkdir build
cd build
git submodule update --init --recursive

cmake ..

make

