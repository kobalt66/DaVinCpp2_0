#include "Application.h"
#include <DaVinCppMacros.h>
#include <rendering/renderables/Square.h>
#include <rendering/renderables/Triangle.h>
#include <rendering/renderables/Circle.h>
#include <Color.h>

namespace davincpp
{
	void Application::onStartEngine()
	{
		ASSERT_ENGINE_CALL(Console::onLoad(), "onStartEngine: loading console");

		ASSERT_ENGINE_CALL(m_ProjectManager = std::make_shared<ProjectManager>("[TEST_ENV]/davincpp.yaml"), "onStartEngine: creating project manager");
		ASSERT_ENGINE_CALL(m_ProjectManager->loadProjectList(), "onStartEngine: loading projects");

		ASSERT_ENGINE_CALL({
			m_SelectionMenu = std::make_unique<SelectionMenu>(m_ProjectManager);
			m_SelectionMenu->onLoad();
			}, "onStartEngine: creating selection menu");

		Console::clear();

		m_SelectionMenu->onExecute();
		
		Console::clear();
	}

	void Application::onLoad()
	{
		Console::log("Loading application...");

		Console::log("Loading DaVinCpp project...");
		ASSERT_LETHAL_ENGINE_CALL(loadSelectedProject(), "onLoad: loading DaVinCpp project");

		ASSERT_ENGINE_CALL({
			const ProjectConfig& projectConfig = m_DaVinCppProject->getProjectConfig();
			m_Window = std::make_unique<Window>(projectConfig);
			m_Window->onSetup();

			Window::flipTexturesH(m_DaVinCppProject->getProjectConfig().FlipTexturesH);
			m_Window->setVsync(projectConfig.Vsync);
			m_Window->showCursor(projectConfig.ShowCursor);
			m_Window->showFps(projectConfig.DebugMode);
		}, "onLoad: creating window");

		ASSERT_ENGINE_CALL(m_GameObjectManager = std::make_unique<GameObjectManager>(), "onLoad: creating game object manager");

		auto square = new GameObject("Square");
		square->setComponent(new Square(glm::vec2(10), GREEN, 6.0f, 6.0f, false));
		square->setComponent(new Texture2D("[BASE_DIR]src/data/Cursor.png", false));
		m_GameObjectManager->registerGameObject(square);

		//GameObject* square2 = new GameObject("Square");
		//square2->setComponent(new Square(glm::vec2(200, 50), WHITE, 10.0f, 10.0f, true));
		//m_GameObjectManager->registerGameObject(square2);
		//
		//GameObject* square3 = new GameObject("Square");
		//square3->setComponent(new Square(glm::vec2(10, 59), glm::vec4(100.0f, 12.0f, 43.0f, 200.0f), 10.0f, 10.0f, true));
		//m_GameObjectManager->registerGameObject(square3);
		//
		//GameObject* triangle = new GameObject("Triangle");
		//triangle->setComponent(new Triangle(glm::vec2(200, 0), glm::vec2(20, 5), glm::vec2(0, 50), RED));
		//triangle->setComponent(new Texture2D("[BASE_DIR]src/data/Cursor.png", true));
		//m_GameObjectManager->registerGameObject(triangle);

		auto triangle2 = new GameObject("Triangle");
		triangle2->setComponent(new Triangle(glm::vec2(200, 50), glm::vec2(200, 100), glm::vec2(300, 50), RED));
		triangle2->setComponent(new Texture2D("[BASE_DIR]src/data/Cursor.png", true));
		m_GameObjectManager->registerGameObject(triangle2);

		auto triangle3 = new GameObject("Triangle");
		triangle3->setComponent(new Triangle(glm::vec2(200, 100), glm::vec2(250, 100), glm::vec2(350, 50), RED));
		triangle3->setComponent(new Texture2D("[BASE_DIR]src/data/Cursor.png", true));
		m_GameObjectManager->registerGameObject(triangle3);

		//GameObject* line = new GameObject("Line");
		//line->setComponent(new Line(glm::vec2(20, 50), glm::vec2(20, 5), 50.0f, BLUE));
		//m_GameObjectManager->registerGameObject(line);
		//
		auto circle = new GameObject("Circle");
		circle->setComponent(new Circle(glm::vec2(100), 24.0f, GRAY, true));
		circle->setComponent(new Texture2D("[BASE_DIR]src/data/Cursor.png", true));
		m_GameObjectManager->registerGameObject(circle);

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


	void Application::loadSelectedProject()
	{
		if (m_ProjectManager->getProjectList().empty()) {
			throw davincpp_error("Failed to load DaVinCpp project: no projects are registered!");
		}

		int projectIdx = m_SelectionMenu->getSelectedProjectIdx();

		if (projectIdx >= m_ProjectManager->getProjectList().size()) {
			throw davincpp_error("Failed to load DaVinCpp project: project index out of project list range!");
		}

		m_DaVinCppProject = std::make_shared<Project>(m_ProjectManager->getProjectList().at(projectIdx));
		Console::log("Successfully loaded DaVinCpp project '", m_DaVinCppProject->getProjectConfig().ProjectName, "'...");
	}
}
