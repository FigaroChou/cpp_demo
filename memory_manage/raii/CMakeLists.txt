cmake_minimum_required(VERSION 3.24)
project(raii)

set(CMAKE_CXX_STANDARD 11)

add_executable(raii main.cpp simple_shared_ptr.cpp)
