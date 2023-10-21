cmake_minimum_required(VERSION 3.26)
project(PA6)

set(CMAKE_CXX_STANDARD 14)

include_directories(PA6_starter_files)

add_executable(PA6
        PA6_starter_files/main.cpp
        PA6_starter_files/Project6.cpp
        PA6_starter_files/Recursion.h
        PA6_starter_files/story.cpp
        PA6_starter_files/story.h)
