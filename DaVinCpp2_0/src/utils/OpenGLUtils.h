#pragma once
#include <opengl.h>

namespace davincpp
{
	class OpenGLUtils
	{
	public:
		static void loadGFLW();
		static void loadOpenGL();
		static void setGLErrorCallback();
		static void setWindowHints(uint32_t glVersionMinor, uint32_t glVersionMajor, uint32_t glProfile);
		static GLFWwindow* createWindow(uint32_t width, uint32_t height, const char* title);
	};
}
