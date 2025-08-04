cmake_minimum_required(VERSION 3.24)
project(test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test main.cpp dynamic_array.h dynamic_array.cpp memory_pool.h memory_pool.cpp)
