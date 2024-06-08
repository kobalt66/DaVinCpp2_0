#pragma once
#include <cstdint>
#include <string>
#include <opengl.h>
#include <window/GameWindow.h>

namespace davincpp
{
	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, const char* title);

		void onSetup();
		static void onResize(GLFWwindow* windowID, int width, int height);
		static void onMousePosition(GLFWwindow* windowID, double xpos, double ypos);
		void onUpdate();
		void onNewFrame();
		void onRender();
		void onShutdown();

		void setVsync(bool vsync);
		void updateViewport();
		glm::ivec2 getMousePos() const;
		bool shouldClose() const;

	private:
		uint32_t m_Width, m_Height;
		const char* m_Title;

		GLFWwindow* m_WindowPtr = nullptr;
		GameWindow m_GameWindow;

		glm::ivec2 m_MousePos = glm::ivec2(0);
	};
}
