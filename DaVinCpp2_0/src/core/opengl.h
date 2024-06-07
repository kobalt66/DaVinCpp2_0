#pragma once

#include <glad/glad.h>
#include <glfw3/glfw3.h>
#include <glm/glm.hpp>
#include <Console.h>

#define GLCall(x) {\
    x;\
    while (GLenum error = glGetError()) { \
        Console::openglErr("(", error, "): ", #x, " ", __FILE__, " : ", __LINE__, ")"); \
        __debugbreak(); \
        exit(1); \
    } \
}
