cmake_minimum_required(VERSION 3.14)
project(Asteroids)

file(GLOB GAME_SRCS
        Bullet.h
        Bullet.cpp
        Player.h
        Player.cpp
        Asteroids.h
        Asteroids.cpp
)

add_library(CoreLib STATIC
        ${GLAD_SRCS}
        ${STB_SRCS}
        ${GAME_SRCS}
)
add_library(Core SHARED
        ${GLAD_SRCS}
        ${STB_SRCS}
        ${GAME_SRCS}
)

target_link_libraries(CoreLib PRIVATE XnCore glfw fmt::fmt)
target_link_libraries(Core PRIVATE XnCore glfw fmt::fmt)
