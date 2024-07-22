#pragma once
#include <opengl.h>
#include <unordered_map>

namespace davincpp
{
	class InputManager
	{
	public:
		static bool isKeyPressed(std::string_view key);
		static bool isKeyReleased(std::string_view key);
		
		static void setWindowPtr(GLFWwindow* windowPtr);

	private:
		static int translateKey(std::string_view key);

	private:
		static std::unordered_map<std::string, int> m_InputMap;
		static GLFWwindow* m_WindowPtr;
	};
}
