cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

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
        ../Resources/XenTheme.h
        App.h
        App.cpp
        MenuBar.cpp
        MenuBar.h
        Window.cpp
        Window.h
        Widgets.cpp
        Widgets.h
)

target_link_libraries(XnApp PRIVATE glfw)