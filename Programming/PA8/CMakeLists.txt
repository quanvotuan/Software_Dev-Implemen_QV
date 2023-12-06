cmake_minimum_required(VERSION 3.26)
project(PA8)

set(CMAKE_CXX_STANDARD 14)

include_directories(PA8_starter_files)

add_executable(PA8_test
        PA8_starter_files/BaseMemoryController.cpp
        PA8_starter_files/BaseMemoryController.hpp
        PA8_starter_files/Heap.cpp
        PA8_starter_files/Heap.hpp
        PA8_starter_files/main.cpp
        PA8_starter_files/MyMemoryController.cpp
        PA8_starter_files/MyMemoryController.hpp
        PA8_starter_files/Lab8_test_case_QV.cpp)