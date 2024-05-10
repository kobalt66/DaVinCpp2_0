#include "Application.h"
#include <string>
#include "Console.h"

namespace davincpp
{
	void Application::onLoad()
	{
		Console::log("Loading application...");
	}

	void Application::onRender()
	{

	}

	void Application::onUpdate()
	{

	}

	void Application::onShutdown()
	{
		Console::wrn("Shutting application down...");
	}

	bool Application::shouldShutdown()
	{
		return m_ShutDown;
	}
}
