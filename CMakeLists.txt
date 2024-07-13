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
)

# Add the executable target
add_executable(DaVinCpp2_0 ${SOURCES}
        DaVinCpp2_0/src/utils/DaVinCppExceptions.cpp)

# Create an imported target for GLFW
add_library(glfw STATIC IMPORTED)

find_package(OpenGL REQUIRED)

# Set the path to libglfw3.a
set(GLFW_LIB_PATH "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries/libglfw3.a")

# Set the path to GLFW include directory
set(GLFW_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/libraries")

# Check if the library file exists
if(NOT EXISTS ${GLFW_LIB_PATH})
    message(FATAL_ERROR "GLFW library not found at ${GLFW_LIB_PATH}")
endif()

# Check if the include directory exists
if(NOT EXISTS ${GLFW_INCLUDE_PATH})
    message(FATAL_ERROR "GLFW include directory not found at ${GLFW_INCLUDE_PATH}")
endif()

set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${GLFW_LIB_PATH}"
        INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_PATH}"
)

add_library(glad "${CMAKE_SOURCE_DIR}/DaVinCpp2_0/glad.c")

# Link libraries
target_link_libraries(DaVinCpp2_0 PRIVATE glfw glad OpenGL::GL)

# On Linux, you might need to link against additional system libraries
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
        "DaVinCpp2_0/src/utils"
)
