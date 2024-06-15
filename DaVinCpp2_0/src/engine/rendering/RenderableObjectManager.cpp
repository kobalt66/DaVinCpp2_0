#include "RenderableObjectManager.h"

namespace davincpp
{
	void RenderableObjectManager::onRender(FrameBuffer& frameBuffer)
	{
		for (std::unique_ptr<Renderable>& renderableObject : m_RenderableObjects) {
			renderableObject->onRender(frameBuffer);
		}
	}

	void RenderableObjectManager::registerRenderableObject(std::unique_ptr<Renderable>&& renderableObject)
	{
		m_RenderableObjects.emplace_back(std::move(renderableObject));
	}
}
