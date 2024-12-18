#pragma once
#include <Window.h>
#include <gameobjects/GameObjectManager.h>
#include <gameprojects/ProjectManager.h>
#include <ui/menu/SelectionMenu.h>
#include <memory>

namespace davincpp
{
	class Application
	{
	public:
		Application() = default;

		void onStartEngine();
		void onLoad();
		void onClear();
		void onUpdate();
		void onRender();
		void onShutdown();
		bool shouldShutdown();

	private:
		void loadSelectedProject();

	private:
		std::unique_ptr<Window> m_Window = nullptr;
		std::unique_ptr<GameObjectManager> m_GameObjectManager = nullptr;
		std::shared_ptr<ProjectManager> m_ProjectManager = nullptr;
		std::unique_ptr<SelectionMenu> m_SelectionMenu = nullptr;

		std::shared_ptr<Project> m_DaVinCppProject = nullptr;

	public:
		static std::string DaVinCppVerison;
	};
}
