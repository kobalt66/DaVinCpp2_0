#pragma once
#include <rendering/Texture2D.h>
#include <gameobjects/GameObjectStats.h>
#include <gameobjects/components/Component.h>

namespace davincpp
{
	class GameObject
	{
	public:
		GameObject(std::string objectName);

		void setComponent(Component* component);
		std::shared_ptr<Component> getComponent(ComponentType uniqueType) const;

		void onLoad();
		void onRender(FrameBuffer& frameBuffer) const;
		void onUpdate();

		void setName(const char* name);
		std::string getName() const;

		/// TODO:	Add functions, like the once in the component class, that allow the gamobject to be correctly
		///			rendered/represented in the engine's UI.

	private:
		GameObjectStats m_Stats;

		std::unordered_map<ComponentType, std::shared_ptr<Component>> m_Components;

		std::weak_ptr<Component> m_RenderingSurface;
		std::weak_ptr<Component> m_Texture;

		/// TODO: Add support for Davscripts and maybe other types of components
	};
}
