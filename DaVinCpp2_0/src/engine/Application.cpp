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
		ASSERT_ENGINE_CALL({
			m_Window = std::make_unique<Window>(1200, 740, "DaVinCpp 2.0");
			m_Window->onSetup();
			m_Window->showCursor(false);
			m_Window->setVsync(false);
			m_Window->showFps(true);
			m_Window->flipTexturesH(true);
		}, "onLoad: creating window");

		ASSERT_ENGINE_CALL(m_GameObjectManager = std::make_unique<GameObjectManager>(), "onLoad: creating game object manager");

		GameObject* square = new GameObject("Square");
		square->setComponent(new Square(glm::vec2(10), GREEN, 60.0f, 30.0f, false));
		square->setComponent(new Texture2D("D:\\C++\\DaVinCpp 2_0\\DaVinCpp2_0\\DaVinCpp2_0\\src\\data\\Cursor.png", true));
		m_GameObjectManager->registerGameObject(square);

		//GameObject* square2 = new GameObject("Square");
		//square2->setComponent(new Square(glm::vec2(20, 50), WHITE, 10.0f, 10.0f, true));
		//m_GameObjectManager->registerGameObject(square2);
		//
		//GameObject* square3 = new GameObject("Square");
		//square3->setComponent(new Square(glm::vec2(10, 59), glm::vec4(100.0f, 12.0f, 43.0f, 200.0f), 10.0f, 10.0f, true));
		//m_GameObjectManager->registerGameObject(square3);
		//
		//GameObject* triangle = new GameObject("Triangle");
		//triangle->setComponent(new Triangle(glm::vec2(80, 0), glm::vec2(20, 5), glm::vec2(0, 50), RED));
		//m_GameObjectManager->registerGameObject(triangle);
		//
		//GameObject* line = new GameObject("Line");
		//line->setComponent(new Line(glm::vec2(20, 50), glm::vec2(20, 5), 50.0f, BLUE));
		//m_GameObjectManager->registerGameObject(line);
		//
		//GameObject* circle = new GameObject("Circle");
		//circle->setComponent(new Circle(glm::vec2(200, 100), 100.0f, GRAY));
		//m_GameObjectManager->registerGameObject(circle);

		ASSERT_ENGINE_CALL(m_GameObjectManager->onLoad(), "onLoad: loading game objects");
	}
	
	void Application::onClear()
	{
		ASSERT_ENGINE_CALL(m_Window->onNewFrame(), "onClear: create new frame");
	}

	void Application::onRender()
	{
		ASSERT_ENGINE_CALL(m_GameObjectManager->onRender(m_Window->getFrameBuffer()), "onRender: rendering game objects");
		ASSERT_ENGINE_CALL(m_Window->onRender(), "onRender: rendering window");
	}

	void Application::onUpdate()
	{
		ASSERT_ENGINE_CALL(m_GameObjectManager->onUpdate(), "onUpdate: updating game objects");
		ASSERT_ENGINE_CALL(m_Window->onUpdate(), "onUpdate: update window");
	}

	void Application::onShutdown()
	{
		Console::wrn("Shutting application down...");
		ASSERT_ENGINE_CALL(m_GameObjectManager->onShutdown(), "onShutdown: sutdown game object manager");
		ASSERT_ENGINE_CALL(m_Window->onShutdown(), "onShutdown: shutdown window");
	}

	bool Application::shouldShutdown()
	{
		return m_Window->shouldClose();
	}
}
