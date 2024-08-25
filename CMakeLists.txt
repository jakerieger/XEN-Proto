cmake_minimum_required(VERSION 3.14glfw)

if (WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows-static)
endif ()

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
        Shared/Vendor/stb_image.cpp
        Core/Game.h
        Core/Game.cpp
        Core/Memory/ThreadPool.cpp
        Core/Memory/ThreadPool.h
        Shared/Types.h
        Shared/IO.h
        Core/GraphicsContext.cpp
        Core/GraphicsContext.h
        Core/Scene.cpp
        Core/Scene.h
        Core/Config.cpp
        Core/Config.h
        Core/PipelineStates.cpp
        Core/PipelineStates.h
        Core/GameObject.cpp
        Core/GameObject.h
        Core/Memory/PoolAllocator.h
        Core/SceneContext.cpp
        Core/SceneContext.h
        Core/Memory/ArenaAllocator.cpp
        Core/Memory/ArenaAllocator.h
        Core/Clock.cpp
        Core/Clock.h
        Core/Primitives.h
        Core/Components/SpriteRenderer.cpp
        Core/Components/SpriteRenderer.h
        Core/Shader.cpp
        Core/Shader.h
        Core/TextureLoader.cpp
        Core/TextureLoader.h
        Core/Camera.cpp
        Core/Camera.h
        Core/Component.cpp
        Core/Component.h
        Core/Components/Transform.cpp
        Core/Components/Transform.h
        Core/InputEvents.h
        Core/InputManager.cpp
        Core/InputManager.h
        Core/InputMap.h
        Shared/TypeTraits.h
        Core/Memory/Unique.cpp
        Core/Memory/Unique.h
        Core/Memory/Shared.cpp
        Core/Memory/Shared.h
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(GameEngineCore PRIVATE glfw)

add_subdirectory(Examples/Pong)