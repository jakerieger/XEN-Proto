cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Tools/SceneEditor)

include_directories(
        ../../Shared/Vendor/imgui
        ../../Shared/Vendor/imgui/backends
)

add_executable(XENSceneEditor
        ${IMGUI_SRCS}
        ../../Shared/Vendor/glad/glad.h
        ../../Shared/Vendor/glad.c
        main.cpp
)

target_link_libraries(XENSceneEditor PRIVATE glfw)