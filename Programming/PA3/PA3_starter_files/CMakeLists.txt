cmake_minimum_required(VERSION 3.26)
project(PA3_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PA3_starter_files
        main.cpp
        Project3.cpp
        UTString.h)
