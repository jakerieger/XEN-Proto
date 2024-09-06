cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Examples/Pong)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

set(GAME_SOURCES main.cpp
        Ball.h
        Ball.cpp
        Player.h
        Player.cpp
        Opponent.h
        Opponent.cpp
        GameManager.cpp
        GameManager.h
)

if (WIN32)
    add_executable(Pong ${GAME_SOURCES} Res/XenGame.rc)
else ()
    add_executable(Pong ${GAME_SOURCES})
endif ()

target_link_libraries(Pong PRIVATE XnCore glfw fmt::fmt-header-only)

# Copy default engine config
add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Config.ini)

add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets)

add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Res)