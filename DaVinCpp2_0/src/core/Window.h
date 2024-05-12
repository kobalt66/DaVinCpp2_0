#pragma once
#include <cstdint>
#include <string>
#include "opengl.h"

namespace davincpp
{
	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, std::string_view title);

		void onSetup();
		void onUpdate();
		void onNewFrame();
		void onShutdown();

		void setVsync(bool vsync);
		void updateViewport();
		glm::ivec2 getMousePos();
		bool shouldClose();

	private:
		uint32_t m_Width, m_Height;
		std::string_view m_Title;

		GLFWwindow* m_WindowPtr = nullptr;

		static glm::ivec2 m_MousePos;
	};
}
