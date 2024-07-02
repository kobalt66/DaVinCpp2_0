#pragma once
#include <gameobjects/GameObject.h>
#include <vector>

namespace davincpp
{
	class GameObjectManager
	{
	public:
		GameObjectManager() = default;

		void onLoad();
		void onRender(FrameBuffer& frameBuffer);
		void onUpdate();
		void onShutdown();

		void registerGameObject(GameObject* gameObject);

	private:
		void validateGameObjectNaming(GameObject* gameObject);

	private:
		std::vector<std::string> m_GameObjectNames;
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
	};
}
