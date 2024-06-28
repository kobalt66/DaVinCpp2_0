#include "GameObject.h"
#include <DaVinCppExceptions.h>

namespace davincpp
{
	GameObject::GameObject(std::string_view objectName)
		: m_ObjectName(objectName.data())
	{ }


	void GameObject::setComponent(Component* component)
	{
		if (m_Components.find(component->getUniqueType()) != m_Components.end()) {
			throw davincpp_error(Console::fmtTxt("Failed to add component to GameObject(", m_ObjectName, "): There is already a component with the same type attached to this game object!"));
		}

		m_Components[component->getUniqueType()] = std::shared_ptr<Component>(component);
	}

	std::shared_ptr<Component> GameObject::getComponent(ComponentType uniqueType) const
	{
		if (m_Components.find(uniqueType) == m_Components.end()) {
			return nullptr;
		}

		return m_Components.at(uniqueType);
	}


	void GameObject::onLoad()
	{

	}

	void GameObject::onRender() const
	{

	}
	
	void GameObject::onUpdate()
	{

	}
}
