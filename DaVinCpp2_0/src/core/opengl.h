#pragma once

#include <glad/glad.h>
#include <glfw3/glfw3.h>
#include <glm/glm.hpp>
#include <Console.h>

#if defined(_MSC_VER)
    #include <intrin.h>
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #include <csignal>
    #define DEBUG_BREAK() raise(SIGTRAP)
#else
    #define DEBUG_BREAK() /* empty */
#endif

#define GLCall(x) {\
    x;\
    while (GLenum error = glGetError()) { \
        Console::openglErr("(", error, "): ", #x, " ", __FILE__, " : ", __LINE__, ")"); \
        DEBUG_BREAK(); \
        exit(1); \
    } \
}
