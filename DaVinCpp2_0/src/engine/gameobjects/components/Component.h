#pragma once
#include <gameobjects/GameObjectStats.h>
#include <FrameBuffer.h>

namespace davincpp
{
	enum class ComponentType : int
	{
		NONE	= -1,
		SURFACE = 0,
		TEXTURE = 1,
	};

	class Component
	{
	public:
		Component(ComponentType uniqueType);

		virtual void onLoad(GameObjectStats& gameObjectStats) { }
		virtual void onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const { }
		virtual void onUpdate(GameObjectStats& gameObjectStats) { }
		virtual void onShutdown(GameObjectStats& gameObjectStats) { }

		/// TODO:	Add virtual functions that allow the components to get properly rendered on the game engine's UI.
		///			Every component has to be able to get rendered differently inside the engine's UI.

		ComponentType getUniqueType() const;

	private:
		ComponentType m_UniqueType = ComponentType::NONE;
	};
}
