cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ProjectManager)

include_directories(
        ../../Vendor/imgui
        ../../Vendor/imgui/backends
)

if (WIN32)
    add_executable(CreateProject ../Resources/app.rc)
else ()
    add_executable(CreateProject)
endif ()

target_sources(CreateProject PRIVATE
        ../../Shared/IO.h
        main.cpp
)

target_link_libraries(CreateProject PRIVATE XnCore glfw XnApp unofficial::nativefiledialog::nfd fmt::fmt)

if (MSVC)
    add_custom_command(TARGET CreateProject PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/../Resources/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Data)
else ()
    add_custom_command(TARGET CreateProject PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/../Resources/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data)
endif ()