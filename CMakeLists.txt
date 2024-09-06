cmake_minimum_required(VERSION 3.14)
project(XEN-Proto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VCPKG_CMAKE_PATH "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_CMAKE_PATH} CACHE STRING "Vcpkg toolchain file")

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
find_package(fmt CONFIG REQUIRED)

## THIRD PARTY DEPENDENCIES (LOCAL) ##
set(BUILD_EXAMPLES OFF)
set(BUILD_DOCUMENTATION OFF)
set(BUILD_INSTALLER OFF)
set(BUILD_UNIT_TESTS OFF)
set(BUILD_STATIC ON)
set(BUILD_WITH_STATIC_RUNTIME_LIBS ON)
add_subdirectory(Shared/Vendor/rttr)

## LIBRARIES ##
add_subdirectory(XnCore)
add_subdirectory(XnGUI)

## TOOLS ##
add_subdirectory(Tools/XnApp)
add_subdirectory(Tools/Editor)

add_subdirectory(Examples/Pong)
add_subdirectory(Examples/Asteroids)

## TESTING PURPOSES: REMOVE ##
add_subdirectory(Templates/EmptyProject/Runtime)