#pragma once

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
		bool m_ShutDown = false;
	};
}
