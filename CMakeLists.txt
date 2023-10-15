cmake_minimum_required(VERSION 3.26)
project(optimization_methods)

set(CMAKE_CXX_STANDARD 17)

add_executable(optimization_methods main.cpp
        algorithms/dynamic_algorithm.cpp
        "data storage/city.h"
        "data storage/map.h"
        algorithms/genetic_algorithm.h
        algorithms/genetic_algorithm.cpp)
