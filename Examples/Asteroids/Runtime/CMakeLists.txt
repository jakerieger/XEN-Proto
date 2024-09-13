cmake_minimum_required(VERSION 3.14)
project(Asteroids)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Asteroids)

if (WIN32)
    add_executable(Asteroids WIN32
            ${GLAD_SRCS}
            ${STB_SRCS}
            main.cpp
            Res/xn.rc
    )
else ()
    add_executable(Asteroids
            ${GLAD_SRCS}
            ${STB_SRCS}
            main.cpp
    )
endif ()

add_subdirectory(Source)

target_link_libraries(Asteroids PRIVATE
        CoreLib
        XnCore
        glfw
        fmt::fmt
)

if (MSVC)
    add_custom_command(TARGET Asteroids PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/../Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Assets)
    add_custom_command(TARGET Asteroids PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/../Config ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Config)
else ()
    add_custom_command(TARGET Asteroids PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/../Assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets)
    add_custom_command(TARGET Asteroids PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/../Config ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Config)
endif ()