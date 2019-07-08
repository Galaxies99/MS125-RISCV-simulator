cmake_minimum_required(VERSION 3.5)
project(RISC_V)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11 -g")

add_executable(code main.cpp)
