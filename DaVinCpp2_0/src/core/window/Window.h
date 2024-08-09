#pragma once
#include <cstdint>
#include <opengl.h>
#include <window/GameWindow.h>

namespace davincpp
{
	class Window
	{
	public:
		Window() = default;
		explicit Window(const ProjectConfig& projectConfig);

		static void onResize(GLFWwindow* windowID, int width, int height);
		static void onMousePosition(GLFWwindow* windowID, double xpos, double ypos);
		
		void onSetup();
		void onUpdate();
		void onNewFrame();
		void onRender();
		void onShutdown();

		static void setVsync(bool vsync);
		void showCursor(bool showCursor);
		void showFps(bool showFps);
		bool shouldClose() const;

		void updateViewport() const;
		static void setOpenGLSettings();
		void setOpenGLCallbacks();
		static void flipTexturesH(bool flip);
		void defineEvents();

		glm::ivec2 getFrameSize() const;
		FrameBuffer& getFrameBuffer();

	private:
		uint32_t m_Width = 0, m_Height = 0;
		std::string m_Title;

		GLFWwindow* m_WindowPtr = nullptr;
		GameWindow m_GameWindow;
		
		bool m_ShowFps = false;
		int m_FpsCount = 0;
	};
}
