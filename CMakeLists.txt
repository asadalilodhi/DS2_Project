cmake_minimum_required(VERSION 3.10)
project(EventTrafficPredictor)

set(CMAKE_CXX_STANDARD 17)

add_executable(traffic_system
    src/main.cpp
    src/datastructures/IntervalTree.cpp
)