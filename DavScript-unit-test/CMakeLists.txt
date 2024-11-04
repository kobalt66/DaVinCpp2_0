cmake_minimum_required(VERSION 3.10)
project(DavScript VERSION 0.1)
cmake_policy(SET CMP0072 NEW)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDAVSCRIPT_UNIT_TEST)
add_definitions(-DDEBUG_BREAK_POINTS=0)

# Collect all source files
file(GLOB_RECURSE SOURCES
        "./main.cpp"
        "../DaVinCpp2_0/src/davscript/**/*.cpp"
        "../DaVinCpp2_0/src/davscript/*.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppFileSystem.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppExceptions.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppNumeric.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppConstants.cpp"
        "../DaVinCpp2_0/src/utils/DaVinCppString.cpp"
        "../DaVinCpp2_0/src/utils/Console.cpp"
        "../Tests/Units/UnitTest.cpp"
        "../Tests/Units/UnitTestEnvironment.cpp"
        "../DaVinCpp2_0/src/core/time/Timer.cpp"
        "./Tests/*.cpp"
        "./main.cpp"
        "../DaVinCpp2_0/src/davscript/**/*.h"
        "../DaVinCpp2_0/src/davscript/*.h"
        "../DaVinCpp2_0/src/utils/DaVinCppFileSystem.h"
        "../DaVinCpp2_0/src/utils/DaVinCppExceptions.h"
        "../DaVinCpp2_0/src/utils/DaVinCppNumeric.h"
        "../DaVinCpp2_0/src/utils/DaVinCppConstants.h"
        "../DaVinCpp2_0/src/utils/DaVinCppString.h"
        "../DaVinCpp2_0/src/utils/DaVinCppMacros.h"
        "../DaVinCpp2_0/src/utils/Console.h"
        "../Tests/Units/UnitTest.h"
        "../Tests/Units/UnitTestEnvironment.h"
        "../DaVinCpp2_0/src/core/time/Timer.h"
        "./Tests/*.h"
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
        "../DaVinCpp2_0/src/davscript/**"
        "../DaVinCpp2_0/src/utils"
        "../DaVinCpp2_0/src/core/time"
        "../Tests/Units"
        "./Tests"
)