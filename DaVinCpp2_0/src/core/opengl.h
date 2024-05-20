#pragma once

#include <glad/glad.h>
#include <glfw3/glfw3.h>
#include <glm/glm.hpp>
#include <Console.h>

#define GLCall(x) { clear_opengl_errors(); \
    x;\
    while (GLenum error = glGetError()) { \
        __debugbreak(); \
        Console::openglErr("(", error, "): ", #x, " ", __FILE__, " : ", __LINE__, ")"); \
        exit(1); \
    } \
}

static void clear_opengl_errors()
{
    while (glGetError() != GL_NO_ERROR);
}
