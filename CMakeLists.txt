cmake_minimum_required(VERSION 3.10)
project(DaVinCpp2_0 VERSION 0.1)
cmake_policy(SET CMP0072 NEW)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files
file(GLOB_RECURSE SOURCES
        "DaVinCpp2_0/main.cpp"
        "DaVinCpp2_0/libraries/**/*.cpp"
        "DaVinCpp2_0/src/**/*.cpp"
        "DaVinCpp2_0/src/davscript/*.cpp"
        "DaVinCpp2_0/src/davscript/*.h"
        "DaVinCpp2_0/libraries/**/*.h"
        "DaVinCpp2_0/src/**/*.h"
)

# Add the executable target
add_executable(DaVinCpp2_0 ${SOURCES})

# Create an imported target for GLFW
add_library(glfw STATIC IMPORTED)

find_package(OpenGL REQUIRED)

set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries/"
)

add_library(glad "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/glad.c")

# Add ncurses
add_library(ncurses STATIC IMPORTED)

set_target_properties(ncurses PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries/libncurses.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries/"
)

# Add yaml-cpp
add_library(yaml-cpp STATIC IMPORTED)

set_target_properties(yaml-cpp PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries/libyaml-cpp.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries/"
)

# Link libraries
target_link_libraries(DaVinCpp2_0 PRIVATE glfw glad OpenGL::GL ncurses yaml-cpp)

# On Linux adding additional system libraries
if(UNIX AND NOT APPLE)
    target_link_libraries(DaVinCpp2_0 PRIVATE
            X11
            Xrandr
            Xinerama
            Xcursor
            pthread
            dl
    )
endif()

# Include directories
target_include_directories(DaVinCpp2_0 PRIVATE
        "DaVinCpp2_0/libraries"
        "DaVinCpp2_0/src/core"
        "DaVinCpp2_0/src/core/window"
        "DaVinCpp2_0/src/engine"
        "DaVinCpp2_0/src/davscript"
        "DaVinCpp2_0/src/utils"
)
