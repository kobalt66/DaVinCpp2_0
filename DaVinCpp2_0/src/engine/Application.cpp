#include "Application.h"
#include <string>
#include <Console.h>

namespace davincpp
{
	void Application::onLoad()
	{
		Console::log("Loading application...");

		m_Window = std::make_unique<Window>(1200, 740, "DaVinCpp 2.0");
	}

	void Application::onRender()
	{
		m_Window->onNewFrame();
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
