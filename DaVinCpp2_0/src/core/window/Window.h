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
		Window() = default;
		Window(uint32_t width, uint32_t height, const char* title);

		static void onResize(GLFWwindow* windowID, int width, int height);
		static void onMousePosition(GLFWwindow* windowID, double xpos, double ypos);
		
		void onSetup();
		void onUpdate();
		void onNewFrame();
		void onRender();
		void onShutdown();

		void setVsync(bool vsync);
		void showCursor(bool showCursor);
		void showFps(bool showFps);
		bool shouldClose() const;

		void updateViewport();
		void setOpenGLSettings();
		void setOpenGLCallbacks();
		void defineEvents();

		glm::ivec2 getFrameSize() const;
		FrameBuffer& getFrameBuffer();

	private:
		uint32_t m_Width, m_Height;
		const char* m_Title;

		GLFWwindow* m_WindowPtr = nullptr;
		GameWindow m_GameWindow;
		
		bool m_ShowFps = false;
		int m_FpsCount = 0;
	};
}
