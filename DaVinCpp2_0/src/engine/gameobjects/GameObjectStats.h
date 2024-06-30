#pragma once
#include <opengl.h>
#include <unordered_map>

namespace davincpp
{
	struct GameObjectStats 
	{
	public:
		GameObjectStats(std::string objectName);

	public:
		std::string m_ObjectName;
		glm::vec2* m_Position = nullptr;
	};
}
