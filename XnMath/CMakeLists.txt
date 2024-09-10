cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

add_library(XnMath STATIC
        Math.h
        Math.cpp
        Vec2.cpp
        Vec2.h
        Vec3.cpp
        Vec3.h
        VectorOperations.h
        Mat4x4.cpp
        Mat4x4.h
        MatrixOperations.h
)

## TEMPORARY TESTING EXE, REMOVE
add_executable(XnMath-Test Test.cpp)
target_link_libraries(XnMath-Test PRIVATE XnMath)