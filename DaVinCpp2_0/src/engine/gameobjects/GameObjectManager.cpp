#include "GameObjectManager.h"
#include <format>

namespace davincpp
{
	void GameObjectManager::onLoad()
	{
		for (const std::pair<std::string, std::shared_ptr<GameObject>>& gameObjectEntry : m_GameObjects) {
			gameObjectEntry.second->onLoad();
		}
	}

	void GameObjectManager::onRender(FrameBuffer& frameBuffer)
	{
		for (const std::pair<std::string, std::shared_ptr<GameObject>>& gameObjectEntry : m_GameObjects) {
			gameObjectEntry.second->onRender(frameBuffer);
		}
	}

	void GameObjectManager::onUpdate()
	{
		for (const std::pair<std::string, std::shared_ptr<GameObject>>& gameObjectEntry : m_GameObjects) {
			gameObjectEntry.second->onUpdate();
		}
	}

	void GameObjectManager::onShutdown()
	{
		m_GameObjects.clear();
	}


	void GameObjectManager::registerGameObject(GameObject* gameObject)
	{
		validateGameObjectNaming(gameObject);
		m_GameObjects[gameObject->getName()]  = std::shared_ptr<GameObject>(gameObject);
	}

	std::shared_ptr<GameObject> GameObjectManager::getGameObject(std::string_view objectName)
	{
		if (m_GameObjects.find(objectName.data()) == m_GameObjects.end()) {
			return nullptr;
		}

		return m_GameObjects.at(objectName.data());
	}


	void GameObjectManager::validateGameObjectNaming(GameObject* gameObject)
	{
		int duplicateCount = 0;
		std::string originalName = gameObject->getName();
		std::string finalName = originalName;

		while (m_GameObjects.find(finalName) != m_GameObjects.end()) {
			finalName = std::format("{} ({})", originalName, ++duplicateCount);
		}

		gameObject->setName(finalName.c_str());
	}
}
