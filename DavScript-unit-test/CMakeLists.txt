cmake_minimum_required(VERSION 3.10)
project(DavScript VERSION 0.1)
cmake_policy(SET CMP0072 NEW)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDAVSCRIPT_UNIT_TEST)

# Collect all source files
file(GLOB_RECURSE SOURCES
        "./main.cpp"
        "../DaVinCpp2_0/src/davscript/**/*.cpp"
        "../DaVinCpp2_0/src/davscript/**/*.h"
        "../DaVinCpp2_0/src/davscript/*.cpp"
        "../DaVinCpp2_0/src/davscript/*.h"
        "../DaVinCpp2_0/src/utils/DaVinCppFileSystem.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppFileSystem.h"
        "../DaVinCpp2_0/src/utils/DaVinCppExceptions.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppExceptions.h"
        "../DaVinCpp2_0/src/utils/DaVinCppNumeric.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppNumeric.h"
        "../DaVinCpp2_0/src/utils/DaVinCppConstants.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppConstants.h"
        "../DaVinCpp2_0/src/utils/DaVinCppString.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppString.h"
        "../DaVinCpp2_0/src/utils/DaVinCppTypes.h"
        "../DaVinCpp2_0/src/utils/Console.cpp"
        "../DaVinCpp2_0/src/utils/Console.h"
)

# Add the executable target
add_executable(DavScript ${SOURCES})

# On Linux adding additional system libraries
if(UNIX AND NOT APPLE)
    target_link_libraries(DavScript PRIVATE
            X11
            Xrandr
            Xinerama
            Xcursor
            pthread
            dl
    )
endif()

target_include_directories(DavScript PRIVATE
        "../DaVinCpp2_0/src/davscript"
        "../DaVinCpp2_0/src/utils"
)