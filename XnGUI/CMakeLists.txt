cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

file(GLOB RMLUI_SRCS ../Vendor/RmlUi/*.cpp ../Vendor/RmlUi/*.h)
add_library(XnGUI STATIC
        ${RMLUI_SRCS}
        InterfaceContext.h
        InterfaceContext.cpp
)

target_link_libraries(XnGUI PRIVATE RmlCore RmlDebugger)