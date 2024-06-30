#pragma once
#include <gameobjects/components/Component.h>

namespace davincpp
{
	class Renderable : public Component
	{
	public:
		Renderable(glm::vec2 position, glm::vec4 color);

		virtual void onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const override;

		virtual glm::vec2 getPosition();
		virtual void setPosition(glm::vec2 position);

	protected:
		glm::vec2 m_Position;
		glm::vec4 m_Color;
	};
}
