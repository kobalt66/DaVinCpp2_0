#include "Application.h"
#include <DaVinCppMacros.h>
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
			std::make_unique<Square>(glm::vec2(10, 50), GREEN, 10.0f, 10.0f, true)
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
		ASSERT_ENGINE_CALL(m_Window->onNewFrame(), "onClear: create new frame");
	}

	void Application::onRender()
	{
		ASSERT_ENGINE_CALL(m_RenderableObjectManager->onRender(m_Window->getFrameBuffer()), "onRender: rendering objects");
		ASSERT_ENGINE_CALL(m_Window->onRender(), "onRender: rendering window");
	}

	void Application::onUpdate()
	{
		ASSERT_ENGINE_CALL(m_Window->onUpdate(), "onUpdate: update window");
	}

	void Application::onShutdown()
	{
		Console::wrn("Shutting application down...");
		ASSERT_ENGINE_CALL(m_Window->onShutdown(), "onShutdown: shutdown window");
	}

	bool Application::shouldShutdown()
	{
		return m_Window->shouldClose();
	}
}
