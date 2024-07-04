#pragma once
#include <gameobjects/GameObject.h>
#include <unordered_map>

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
		std::shared_ptr<GameObject> getGameObject(std::string_view objectName);

	private:
		void validateGameObjectNaming(GameObject* gameObject);

	private:
		std::unordered_map<std::string, std::shared_ptr<GameObject>> m_GameObjects;
	};
}
