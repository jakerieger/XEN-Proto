cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SceneEditor)

include_directories(
        ../../Shared/Vendor/imgui
        ../../Shared/Vendor/imgui/backends
)

if (WIN32)
    add_executable(XENEditor ../Resources/app.rc)
else ()
    add_executable(XENEditor)
endif ()

target_sources(XENEditor PRIVATE
        main.cpp
)

target_link_libraries(XENEditor PRIVATE glfw ImguiApp unofficial::nativefiledialog::nfd)

add_custom_command(TARGET XENEditor PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data)