#include "Window.h"
#include <DaVinCppExceptions.h>

namespace davincpp
{
	glm::ivec2 Window::m_MousePos = glm::ivec2(0);

	Window::Window(uint32_t width, uint32_t height, std::string_view title)
	{ 
		m_Width = width;
		m_Height = height;
		m_Title = title;
	}

	void Window::onSetup()
	{
		if (glfwInit() == -1) {
			Console::err("Failed to initialize glfw!");
			throw glfw_error();
		}

		glfwSetErrorCallback([](int code, const char* msg) {
			Console::openglErr("[GLFW] (", code, ") ", msg);
			});

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		m_WindowPtr = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title.data(), nullptr, nullptr);

		if (m_WindowPtr == nullptr) {
			Console::err("Failed to create window!");
			throw glfw_error();
		}

		glfwMakeContextCurrent(m_WindowPtr);

		if (gladLoadGL() == -1) {
			Console::err("Failed to load OpenGL!");
			throw opengl_error();
		}

		updateViewport();

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		glfwSetCursorPosCallback(m_WindowPtr, [](GLFWwindow* window, double xpos, double ypos) {
			Window::m_MousePos.x = static_cast<int>(xpos);
			Window::m_MousePos.y = static_cast<int>(ypos);
			});
	}
	
	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowPtr);
	}
	
	void Window::onNewFrame()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	
	void Window::onShutdown()
	{
		
	}


	void Window::setVsync(bool vsync)
	{
		glfwSwapInterval((int)vsync);
	}

	void Window::updateViewport()
	{
		GLCall(glViewport(0, 0, m_Width, m_Height));
	}

	glm::ivec2 Window::getMousePos() const
	{
		return m_MousePos;
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(m_WindowPtr);
	}
}
