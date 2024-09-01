cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)

file(GLOB RMLUI_SRCS ../Shared/Vendor/RmlUi/*.cpp ../Shared/Vendor/RmlUi/*.h)
add_library(XnGUI STATIC
        ${RMLUI_SRCS}
        InterfaceContext.h
        InterfaceContext.cpp
)

target_link_libraries(XnGUI PRIVATE RmlCore RmlDebugger)

add_custom_command(TARGET XnGUI PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/BuiltinAssets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Pong/BuiltinAssets)