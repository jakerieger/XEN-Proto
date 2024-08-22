cmake_minimum_required(VERSION 3.29)
project(2DGameEngine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Shared/Vendor
)

add_library(GameEngineCore STATIC
        Shared/Vendor/glad.c
        Core/Game.h
        Core/Game.cpp
        Core/ThreadPool.cpp
        Core/ThreadPool.h
        Shared/Types.h
        Shared/IO.h
        Core/GraphicsContext.cpp
        Core/GraphicsContext.h
        Core/Scene.cpp
        Core/Scene.h
        Core/EngineConfig.cpp
        Core/EngineConfig.h
        Core/PipelineStates.cpp
        Core/PipelineStates.h
        Core/GameObject.cpp
        Core/GameObject.h
        Core/PoolAllocator.cpp
        Core/PoolAllocator.h
        Core/Memory.h
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(GameEngineCore PRIVATE glfw)

add_executable(Pong Examples/Pong.cpp)
target_link_libraries(Pong PRIVATE GameEngineCore glfw)

# Copy default engine config
add_custom_command(TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/EngineConfig.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EngineConfig.ini)