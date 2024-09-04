cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 20)

set(VCPKG_CMAKE_PATH "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_CMAKE_PATH} CACHE STRING "Vcpkg toolchain file")

set(BUILD_EXAMPLES ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB IMGUI_SRCS
        Shared/Vendor/imgui/*.cpp
        Shared/Vendor/imgui/backends/imgui_impl_opengl3.cpp
        Shared/Vendor/imgui/backends/imgui_impl_glfw.cpp
)

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Shared/Vendor
)

## THIRD PARTY DEPENDENCIES (VCPKG) ##
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(AudioFile CONFIG REQUIRED)
find_package(RmlUi CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

## LIBRARIES ##
add_subdirectory(XnCore)
add_subdirectory(XnGUI)
add_subdirectory(XnProfiler)

## TOOLS ##
add_subdirectory(Tools/XnApp)
add_subdirectory(Tools/Editor)

if (${BUILD_EXAMPLES})
    add_subdirectory(Examples/Pong)
    add_subdirectory(Examples/Asteroids)
endif ()