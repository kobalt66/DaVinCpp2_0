#include "Application.h"
#include <string>
#include <rendering/renderables/Square.h>
#include <Color.h>

namespace davincpp
{
	void Application::onLoad()
	{
		Console::log("Loading application...");
		m_Window = std::make_unique<Window>(1200, 740, "DaVinCpp 2.0");
		m_Window->onSetup();
		m_Window->showCursor(false);
		m_Window->setVsync(false);
		m_Window->showFps(true);

		m_RenderableObjectManager = std::make_unique<RenderableObjectManager>();

		m_RenderableObjectManager->registerRenderableObject(
			std::make_unique<Square>(glm::vec2(m_Window->getFrameSize() / 2), GREEN, 10, 10, true)
		);
	}
	
	void Application::onClear()
	{
		m_Window->onNewFrame();
	}

	void Application::onRender()
	{
		m_RenderableObjectManager->onRender(m_Window->getFrameBuffer());
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
