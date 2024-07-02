#include "GameObjectManager.h"
#include <format>

namespace davincpp
{
	void GameObjectManager::onLoad()
	{
		for (const std::unique_ptr<GameObject>& gameObject : m_GameObjects) {
			gameObject->onLoad();
		}
	}

	void GameObjectManager::onRender(FrameBuffer& frameBuffer)
	{
		for (const std::unique_ptr<GameObject>& gameObject : m_GameObjects) {
			gameObject->onRender(frameBuffer);
		}
	}

	void GameObjectManager::onUpdate()
	{
		for (const std::unique_ptr<GameObject>& gameObject : m_GameObjects) {
			gameObject->onUpdate();
		}
	}

	void GameObjectManager::onShutdown()
	{
		m_GameObjectNames.clear();
		m_GameObjects.clear();
	}


	void GameObjectManager::registerGameObject(GameObject* gameObject)
	{
		validateGameObjectNaming(gameObject);
		m_GameObjectNames.emplace_back(gameObject->getName());
		m_GameObjects.emplace_back(gameObject);
	}


	void GameObjectManager::validateGameObjectNaming(GameObject* gameObject)
	{
		int duplicateCount = 0;
		std::string originalName = gameObject->getName();
		std::string finalName = originalName;

		while (std::find(m_GameObjectNames.begin(), m_GameObjectNames.end(), finalName) != m_GameObjectNames.end()) {
			finalName = std::format("{} ({})", originalName, ++duplicateCount);
		}

		gameObject->setName(finalName.c_str());
	}
}
