#!/bin/bash

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
