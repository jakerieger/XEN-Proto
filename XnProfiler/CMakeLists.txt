cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)

add_library(XnProfiler STATIC
        Profiler.h
        Profiler.cpp
)

target_link_libraries(XnProfiler)