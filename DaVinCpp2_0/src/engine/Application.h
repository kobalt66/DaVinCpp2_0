#pragma once

#include <Window.h>
#include <memory>

namespace davincpp
{
	class Application
	{
	public:
		Application() = default;

		void onLoad();
		void onUpdate();
		void onRender();
		void onShutdown();
		bool shouldShutdown();

	private:
		std::unique_ptr<Window> m_Window = nullptr;
	};
}
