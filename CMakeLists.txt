cmake_minimum_required(VERSION 3.14)
project(2DGameEngine)

set(CMAKE_CXX_STANDARD 20)

set(VCPKG_CMAKE_PATH "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_CMAKE_PATH} CACHE STRING "Vcpkg toolchain file")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Shared/Vendor
)

add_library(GameEngineCore STATIC
        Shared/Vendor/glad.c
        Shared/Vendor/stb_image.cpp
        Shared/Types.h
        Shared/TypeTraits.h
        Shared/IO.h
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
        Core/Memory/Unique.h
        Core/Memory/Shared.cpp
        Core/Memory/Shared.h
        Core/EventSystem.h
        Core/Events.h
        Core/Components/Rigidbody.cpp
        Core/Components/Rigidbody.h
        Core/AudioContext.cpp
        Core/AudioContext.h
        Core/AudioChannel.h
        Core/AudioUtils.h
        Core/Math/Vector2.cpp
        Core/Math/Vector2.h
        Core/Math/Matrix4x4.cpp
        Core/Math/Matrix4x4.h
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(AudioFile CONFIG REQUIRED)
target_link_libraries(GameEngineCore PRIVATE glfw glm::glm-header-only OpenAL::OpenAL AudioFile)

add_subdirectory(Examples/Pong)