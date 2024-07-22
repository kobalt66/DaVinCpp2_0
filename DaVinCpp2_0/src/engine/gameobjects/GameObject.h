#pragma once
#include <rendering/Texture2D.h>

namespace davincpp
{
	struct GameObjectStats;

	class GameObject
	{
	public:
		explicit GameObject(std::string objectName = "game object");

		void setComponent(Component* component);
		std::shared_ptr<Component> getComponent(ComponentType uniqueType) const;

		void onLoad();
		void onRender(FrameBuffer& frameBuffer) const;
		void onUpdate();

		void setName(const char* name);
		std::string getName() const;
		
		template<class T> std::shared_ptr<T> getRenderingSurface() const
		{
			return std::dynamic_pointer_cast<T>(m_RenderingSurface.lock());
		}

		std::shared_ptr<Texture2D> getTexture() const;
		GameObjectStats& getStats();

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
