#include "Window.h"
#include <events/EventHandler.h>
#include <rendering/Texture2D.h>
#include <OpenGLUtils.h>
#include <input/InputManager.h>

namespace davincpp
{
	Window::Window(const ProjectConfig& projectConfig)
		: m_Width(projectConfig.ScreenResolution.x),
		m_Height(projectConfig.ScreenResolution.y),
		m_Title(projectConfig.ProjectName)
	{ }


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
		window->m_GameWindow.onMousePosition(xpos, ypos);
	}


	void Window::onSetup()
	{
		OpenGLUtils::loadGFLW();
		OpenGLUtils::setGLErrorCallback();
		OpenGLUtils::setWindowHints(4, 4, GLFW_OPENGL_CORE_PROFILE);
		
		m_WindowPtr = OpenGLUtils::createWindow(m_Width, m_Height, m_Title.c_str());

		glfwMakeContextCurrent(m_WindowPtr);

		OpenGLUtils::loadOpenGL();

		updateViewport();
		setOpenGLSettings();
		setOpenGLCallbacks();
		defineEvents();

		m_GameWindow.onSetup();
		m_GameWindow.onResize(m_Width, m_Height);

		InputManager::setWindowPtr(m_WindowPtr);
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowPtr);
		m_FpsCount++;

		EventHandler::onUpdate();
		m_GameWindow.onUpdate();
	}

	void Window::onNewFrame()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		m_GameWindow.onClear();
	}


	void Window::onRender()
	{
		m_GameWindow.onRender();
	}
	
	void Window::onShutdown()
	{
		
	}


	void Window::setVsync(bool vsync)
	{
		glfwSwapInterval((int)vsync);
	}

	void Window::showCursor(bool showCursor)
	{
		glfwSetInputMode(m_WindowPtr, GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
	}

	void Window::showFps(bool showFps)
	{
		m_ShowFps = showFps;
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(m_WindowPtr);
	}



	void Window::updateViewport() const
	{
		GLCall(glViewport(0, 0, m_Width, m_Height));
	}

	void Window::setOpenGLSettings()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glClearColor(0, 0, 0, 0));
	}

	void Window::setOpenGLCallbacks()
	{
		glfwSetWindowUserPointer(m_WindowPtr, reinterpret_cast<void*>(this));
		glfwSetWindowSizeCallback(m_WindowPtr, Window::onResize);
		glfwSetCursorPosCallback(m_WindowPtr, Window::onMousePosition);
	}

	void Window::flipTexturesH(bool flip) 
	{
		Texture2D::flipTexturesH(flip);
	}

	void Window::defineEvents()
	{
		EventHandler::addEvent(Event([&]() {
			if (!m_ShowFps) {
				glfwSetWindowTitle(m_WindowPtr, m_Title.c_str());
				return;
			}

			std::string alteredWindowTitle = std::string(std::string(m_Title) + " | Fps: " + std::to_string(m_FpsCount));
			glfwSetWindowTitle(m_WindowPtr, alteredWindowTitle.c_str());
			m_FpsCount = 0;
			}, sec(1), true));
	}


	glm::ivec2 Window::getFrameSize() const
	{
		return m_GameWindow.getFrameSize();
	}

	FrameBuffer& Window::getFrameBuffer()
	{
		return m_GameWindow.getFrameBuffer();
	}
}
