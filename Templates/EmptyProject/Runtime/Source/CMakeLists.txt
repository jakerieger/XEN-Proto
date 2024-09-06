cmake_minimum_required(VERSION 3.14)
project(Empty)

add_library(EmptyStatic STATIC Empty.h Empty.cpp)
add_library(EmptyShared SHARED Empty.h Empty.cpp)