cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

include_directories(
        ../../ThirdParty/imgui
        ../../ThirdParty/imgui/backends
)

add_library(XnApp STATIC
        ${IMGUI_SRCS}
        ${STB_SRCS}
        ${GLAD_SRCS}
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