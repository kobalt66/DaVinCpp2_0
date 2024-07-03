#pragma once
#include <gameobjects/components/Component.h>
#include <gameobjects/GameObject.h>

namespace davincpp
{
	class Renderable : public Component
	{
	public:
		Renderable(glm::vec2 position, glm::vec4 color);

		void onLoad(GameObjectStats& gameObjectStats) override;
		virtual void onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const override;

		virtual glm::vec2 getPosition();
		virtual void setPosition(glm::vec2 position);

	protected:
		glm::vec4 mapTextureByUVCoords(std::shared_ptr<Texture2D> texture, int pixelX, int pixelY, float width, float height) const;
			 
	protected:
		glm::vec2 m_Position;
		glm::vec4 m_Color;
	};
}
