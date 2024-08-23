cmake_minimum_required(VERSION 3.14)
project(2DGameEngine)

include_directories(
        ${CMAKE_SOURCE_DIR}
)

add_executable(Pong
        Pong.cpp
        Ball.h
        Ball.cpp
        Player.h
        Player.cpp
        Opponent.h
        Opponent.cpp
)

target_link_libraries(Pong PRIVATE GameEngineCore glfw)

# Copy default engine config
add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/EngineConfig.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EngineConfig.ini)

add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets)