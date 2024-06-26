#include "Application.h"
#include <string>
#include <rendering/renderables/Square.h>
#include <rendering/renderables/Triangle.h>
#include <rendering/renderables/Line.h>
#include <rendering/renderables/Circle.h>
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
			std::make_unique<Square>(glm::vec2(10, 50), GREEN, 10, 10, true)
		);

		m_RenderableObjectManager->registerRenderableObject(
			std::make_unique<Triangle>(glm::vec2(80, 0), glm::vec2(20, 5), glm::vec2(0, 50), RED)
		);

		m_RenderableObjectManager->registerRenderableObject(
			std::make_unique<Line>(glm::vec2(20, 50), glm::vec2(20, 5), 50.0f, BLUE)
		);

		m_RenderableObjectManager->registerRenderableObject(
			std::make_unique<Circle>(glm::vec2(200, 100), 100.0f, GRAY)
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
