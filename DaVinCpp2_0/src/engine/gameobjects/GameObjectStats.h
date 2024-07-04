#pragma once
#include <opengl.h>
#include <unordered_map>

namespace davincpp
{
	class GameObject;

	struct GameObjectStats 
	{
	public:
		GameObjectStats(GameObject* objectPtr, std::string objectName);

	public:
		GameObject* m_ObjectPtr;
		std::string m_ObjectName;
		glm::vec2* m_Position = nullptr;
	};
}
