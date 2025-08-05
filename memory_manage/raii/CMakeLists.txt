cmake_minimum_required(VERSION 3.24)
project(raii)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "/opt/gcc-9.5.0/bin/gcc")
set(CMAKE_CXX_COMPILER "/opt/gcc-9.5.0/bin/g++")

add_executable(raii main.cpp simple_shared_ptr.cpp)
