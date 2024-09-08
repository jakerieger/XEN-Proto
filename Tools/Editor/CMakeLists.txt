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
            FileTemplates.h
            GameProcess.h
            ../ProjectManager/main.cpp)
endif ()

target_sources(XENEditor PRIVATE
        ../../Shared/IO.h
        main.cpp
        CachedLayout.h
        FileTemplates.h
        GameProcess.h
)

target_link_libraries(XENEditor PRIVATE XnCore glfw XnApp unofficial::nativefiledialog::nfd fmt::fmt)

if (MSVC)
    add_custom_command(TARGET XENEditor PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ../Resources/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Data)
else ()
    add_custom_command(TARGET XENEditor PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ../Resources/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data)
endif ()