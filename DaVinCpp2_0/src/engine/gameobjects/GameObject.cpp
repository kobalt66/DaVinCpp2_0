#include "GameObject.h"
#include <DaVinCppExceptions.h>
#include <gameobjects/GameObjectStats.h>

namespace davincpp
{
	GameObject::GameObject(std::string objectName)
		: m_Stats(this, objectName)
	{ }


	void GameObject::setComponent(Component* component)
	{
		if (component->getUniqueType() == ComponentType::NONE) {
			throw davincpp_error(Console::fmtTxt("Failed to add component to GameObject(", m_Stats.m_ObjectName, "): component has not valid type associated!"));
		}

		if (m_Components.contains(component->getUniqueType())) {
			throw davincpp_error(Console::fmtTxt("Failed to add component to GameObject(", m_Stats.m_ObjectName, "): There is already a component with the same type attached to this game object!"));
		}

		std::shared_ptr<Component> componentPtr = std::shared_ptr<Component>(component);

		switch (component->getUniqueType()) {
		case ComponentType::SURFACE:
			m_RenderingSurface = std::weak_ptr<Component>(componentPtr);
			break;
		case ComponentType::TEXTURE:
			m_Texture = std::weak_ptr<Component>(componentPtr);
			break;
		}

		m_Components[component->getUniqueType()] = componentPtr;
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
		for (std::pair<ComponentType, std::shared_ptr<Component>> component : m_Components) {
			component.second->onLoad(m_Stats);
		}
	}

	void GameObject::onRender(FrameBuffer& frameBuffer) const
	{
		for (const std::pair<ComponentType, std::shared_ptr<Component>> component : m_Components) {
			component.second->onRender(m_Stats, frameBuffer);
		}
	}
	
	void GameObject::onUpdate()
	{
		for (std::pair<ComponentType, std::shared_ptr<Component>> component : m_Components) {
			component.second->onUpdate(m_Stats);
		}
	}


	void GameObject::setName(const char* name)
	{
		m_Stats.m_ObjectName = name;
	}

	std::string GameObject::getName() const
	{
		return m_Stats.m_ObjectName;
	}

	std::shared_ptr<Texture2D> GameObject::getTexture() const
	{
		return std::dynamic_pointer_cast<Texture2D>(m_Texture.lock());
	}

	GameObjectStats& GameObject::getStats()
	{
		return m_Stats;
	}
}
