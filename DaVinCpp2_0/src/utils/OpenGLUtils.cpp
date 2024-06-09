#include "OpenGLUtils.h"
#include <DaVinCppExceptions.h>
#include <opengl.h>

namespace davincpp
{
	void OpenGLUtils::loadGFLW()
	{
		if (glfwInit() != -1) {
			return;
		}

		Console::err("Failed to initialize glfw!");
		throw glfw_error();
	}

	void OpenGLUtils::loadOpenGL()
	{
		if (gladLoadGL() != -1) {
			return;
		}
		
		Console::err("Failed to load OpenGL!");
		throw opengl_error();
	}

	void OpenGLUtils::setGLErrorCallback()
	{
		glfwSetErrorCallback([](int code, const char* msg) { Console::openglErr("[GLFW] (", code, ") ", msg); });
	}

	void OpenGLUtils::setWindowHints(uint32_t glVersionMinor, uint32_t glVersionMajor, uint32_t glProfile)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersionMinor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersionMajor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, glProfile);
	}

	GLFWwindow* OpenGLUtils::createWindow(uint32_t width, uint32_t height, const char* title)
	{
		GLFWwindow* windowPtr = glfwCreateWindow((int)width, (int)height, title, nullptr, nullptr);

		if (windowPtr != nullptr) {
			return windowPtr;
		}

		Console::err("Failed to create window!");
		throw glfw_error();
	}
}
