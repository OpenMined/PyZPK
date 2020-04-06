cmake_minimum_required( VERSION 3.3.0 )
project(PyZPK)

add_subdirectory(third_party/pybind11) 
pybind11_add_module(PyZPK src/main.cpp)