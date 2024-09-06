cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/XENEditor)

include_directories(
        ../../Vendor/imgui
        ../../Vendor/imgui/backends
)

if (WIN32)
    add_executable(XENEditor ../Resources/app.rc)
else ()
    add_executable(XENEditor
            FileTemplates.h)
endif ()

target_sources(XENEditor PRIVATE
        ../../Shared/IO.h
        main.cpp
        CachedLayout.h
        FileTemplates.h
)

target_link_libraries(XENEditor PRIVATE XnCore glfw XnApp unofficial::nativefiledialog::nfd fmt::fmt-header-only)

add_custom_command(TARGET XENEditor PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data)