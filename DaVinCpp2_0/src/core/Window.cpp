#include "Window.h"
#include <Console.h>
#include <exception>

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
		if (!glfwInit()) {
			Console::err("Failed to initialize glfw!");
			throw std::runtime_error("[GLFW]");
		}

		glfwWindowHint(GLFW_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_WindowPtr = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title.data(), nullptr, nullptr);

		if (m_WindowPtr == nullptr) {
			Console::err("Failed to create window!");
			throw std::runtime_error("[WindowPtr]");
		}

		glfwMakeContextCurrent(m_WindowPtr);

		if (gladLoadGL() == -1) {
			Console::err("Failed to load OpenGL!");
			throw std::runtime_error("[OpenGL]");
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

	glm::ivec2 Window::getMousePos()
	{
		return m_MousePos;
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(m_WindowPtr);
	}
}
