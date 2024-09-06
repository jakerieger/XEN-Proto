cmake_minimum_required(VERSION 3.14)
project(Empty)

add_library(EmptyStatic STATIC ../../../../Shared/Vendor/glad.c Empty.h Empty.cpp)
add_library(EmptyShared SHARED ../../../../Shared/Vendor/glad.c Empty.h Empty.cpp)

target_link_libraries(EmptyStatic PRIVATE XnCore glfw fmt::fmt-header-only)
target_link_libraries(EmptyShared PRIVATE XnCore glfw fmt::fmt-header-only)
