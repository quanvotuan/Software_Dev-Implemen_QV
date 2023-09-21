cmake_minimum_required(VERSION 3.26)
project(PA2_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PA2_starter_files
        main.cpp
        MatrixMultiply.h
        Project2.cpp)
