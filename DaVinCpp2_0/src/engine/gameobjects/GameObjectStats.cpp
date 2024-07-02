#include "GameObjectStats.h"
#include <gameobjects/GameObject.h>

namespace davincpp
{
	GameObjectStats::GameObjectStats(GameObject* objectPtr, std::string objectName)
		: m_ObjectPtr(objectPtr), m_ObjectName(objectName)
	{ }
}
