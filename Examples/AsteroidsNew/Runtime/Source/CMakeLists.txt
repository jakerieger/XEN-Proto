cmake_minimum_required(VERSION 3.14)
project(Asteroids)

add_library(CoreLib STATIC ${GLAD_SRCS} ${STB_SRCS} Asteroids.h Asteroids.cpp)
add_library(Core SHARED ${GLAD_SRCS} ${STB_SRCS} Asteroids.h Asteroids.cpp)

target_link_libraries(CoreLib PRIVATE XnCore glfw fmt::fmt-header-only)
target_link_libraries(Core PRIVATE XnCore glfw fmt::fmt-header-only)
