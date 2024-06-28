#pragma once
#include <gameobjects/components/Component.h>
#include <rendering/Texture2D.h>
#include <unordered_map>

namespace davincpp
{
	class GameObject
	{
	public:
		GameObject(std::string_view objectName);

		void setComponent(Component* component);
		std::shared_ptr<Component> getComponent(ComponentType uniqueType) const;

		void onLoad();
		void onRender() const;
		void onUpdate();

		/// TODO:	Add functions, like the once in the component class, that allow the gamobject to be correctly
		///			rendered/represented in the engine's UI.

	private:
		const char* m_ObjectName;
		std::unordered_map<ComponentType, std::shared_ptr<Component>> m_Components;

		std::shared_ptr<Component> m_RenderingSurface = nullptr;
		std::shared_ptr<Component> m_Texture = nullptr;

		/// TODO: Add support for Davscripts and maybe other types of components
	};
}
