#pragma once
#include <Window.h>
#include <gameobjects/GameObjectManager.h>
#include <memory>

namespace davincpp
{
	class Application
	{
	public:
		Application() = default;

		void onLoad();
		void onClear();
		void onUpdate();
		void onRender();
		void onShutdown();
		bool shouldShutdown();

	private:
		std::unique_ptr<Window> m_Window = nullptr;
		std::unique_ptr<GameObjectManager> m_GameObjectManager = nullptr;
	};
}
