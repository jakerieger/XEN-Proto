cmake_minimum_required(VERSION 3.14)
project(2DGameEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Asteroids)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(GAME_SOURCES
        main.cpp
        Player.cpp
        Player.h
        Bullet.cpp
        Bullet.h
)

if (WIN32)
    add_executable(Asteroids ${GAME_SOURCES} Res/XenGame.rc)
else ()
    add_executable(Asteroids ${GAME_SOURCES})
endif ()

target_link_libraries(Asteroids PRIVATE XnCore glfw)

# Copy default engine config
add_custom_command(TARGET Asteroids PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Config.ini)

add_custom_command(TARGET Asteroids PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets)

add_custom_command(TARGET Asteroids PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Res)