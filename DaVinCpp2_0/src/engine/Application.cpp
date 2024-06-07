#include "Application.h"
#include <string>

namespace davincpp
{
	void Application::onLoad()
	{
		Console::log("Loading application...");
		m_Window = std::make_unique<Window>(1200, 740, "DaVinCpp 2.0");
		m_Window->onSetup();
	}

	void Application::onRender()
	{
		m_Window->onNewFrame();
		m_Window->onRender();
	}

	void Application::onUpdate()
	{
		m_Window->onUpdate();
	}

	void Application::onShutdown()
	{
		Console::wrn("Shutting application down...");
		m_Window->onShutdown();
	}

	bool Application::shouldShutdown()
	{
		return m_Window->shouldClose();
	}
}
