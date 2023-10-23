cmake_minimum_required(VERSION 3.26)
project(PA6_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PA6_starter_files
        main.cpp
        Project6.cpp
        Recursion.h
        story.cpp
        story.h)
