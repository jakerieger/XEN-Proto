cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Tools)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Tools)

include_directories(
        ../Shared/Vendor/imgui
        ../Shared/Vendor/imgui/backends
)

add_library(ImguiApp STATIC
        ${IMGUI_SRCS}
        ../Shared/Vendor/stb_image.h
        ../Shared/Vendor/stb_image.cpp
        ../Shared/Vendor/glad/glad.h
        ../Shared/Vendor/glad.c
        ImguiApp.h
        ImguiApp.cpp
)

target_link_libraries(ImguiApp PRIVATE glfw)

add_subdirectory(Editor)