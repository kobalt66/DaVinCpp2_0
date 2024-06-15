#pragma once
#include <rendering/renderables/Renderable.h>
#include <vector>

namespace davincpp
{
	class RenderableObjectManager
	{
	public:
		RenderableObjectManager() = default;

		void onRender(FrameBuffer& frameBuffer);

		void registerRenderableObject(std::unique_ptr<Renderable>&& renderableObject);

	private:
		std::vector<std::unique_ptr<Renderable>> m_RenderableObjects;
	};
}
