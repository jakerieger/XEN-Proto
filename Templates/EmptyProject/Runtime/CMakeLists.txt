cmake_minimum_required(VERSION 3.14)
project(Empty)

if (WIN32)
    add_executable(Empty WIN32 ../../../Shared/Vendor/glad.c main.cpp)
else ()
    add_executable(Empty ../../../Shared/Vendor/glad.c main.cpp)
endif ()

add_subdirectory(Source)

target_link_libraries(Empty PRIVATE EmptyStatic XnCore glfw fmt::fmt-header-only)