cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SceneEditor)

include_directories(
        ../../Shared/Vendor/imgui
        ../../Shared/Vendor/imgui/backends
)

if (WIN32)
    add_executable(XENSceneEditor ../Resources/app.rc)
else ()
    add_executable(XENSceneEditor)
endif ()

target_sources(XENSceneEditor PRIVATE
        main.cpp
)

target_link_libraries(XENSceneEditor PRIVATE glfw ImguiApp)

add_custom_command(TARGET XENSceneEditor PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data)