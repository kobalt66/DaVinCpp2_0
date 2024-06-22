#pragma once
#include <Window.h>
#include <rendering/RenderableObjectManager.h>
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
		std::unique_ptr<RenderableObjectManager> m_RenderableObjectManager = nullptr;
	};
}
