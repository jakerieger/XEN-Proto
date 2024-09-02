cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ../../Shared/Vendor/imgui
        ../../Shared/Vendor/imgui/backends
)

add_library(XnApp STATIC
        ${IMGUI_SRCS}
        ../../Shared/Vendor/stb_image.h
        ../../Shared/Vendor/stb_image.cpp
        ../../Shared/Vendor/glad/glad.h
        ../../Shared/Vendor/glad.c
        App.h
        App.cpp
)

target_link_libraries(XnApp PRIVATE glfw)