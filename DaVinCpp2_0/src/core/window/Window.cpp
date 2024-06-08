#include "Window.h"
#include <DaVinCppExceptions.h>

namespace davincpp
{
	Window::Window(uint32_t width, uint32_t height, const char* title)
		: m_GameWindow(4, 4, 4)
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

		glfwSetErrorCallback([](int code, const char* msg) { Console::openglErr("[GLFW] (", code, ") ", msg); });

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		m_WindowPtr = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title, nullptr, nullptr);

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
		GLCall(glClearColor(0, 0, 0, 0));

		glfwSetWindowUserPointer(m_WindowPtr, reinterpret_cast<void*>(this));
		glfwSetWindowSizeCallback(m_WindowPtr, Window::onResize);
		glfwSetCursorPosCallback(m_WindowPtr, Window::onMousePosition);

		m_GameWindow.onSetup();

		m_GameWindow.onResize(m_Width, m_Height);
	}
	
	void Window::onResize(GLFWwindow* windowID, int width, int height)
	{
		Window* window = static_cast<Window*>(glfwGetWindowUserPointer(windowID));
		window->m_Width = width;
		window->m_Height = height;

		window->m_GameWindow.onResize(width, height);
		window->updateViewport();
	}

	void Window::onMousePosition(GLFWwindow* windowID, double xpos, double ypos)
	{
		Window* window = static_cast<Window*>(glfwGetWindowUserPointer(windowID));
		window->m_MousePos.x = static_cast<int>(xpos / window->m_GameWindow.getPixelSize().x);
		window->m_MousePos.y = window->m_GameWindow.getFrameSize().y - static_cast<int>(ypos / window->m_GameWindow.getPixelSize().y) - 1;
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowPtr);
	}
	
	void Window::onNewFrame()
	{
		m_GameWindow.onClear();
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Window::onRender()
	{
		m_GameWindow.setPixel(m_MousePos.x, m_MousePos.y, glm::vec4(58, 252, 161, 255));
		m_GameWindow.onRender();
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
