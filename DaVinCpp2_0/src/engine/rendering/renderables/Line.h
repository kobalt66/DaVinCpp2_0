#pragma once
#include <rendering/renderables/Renderable.h>

namespace davincpp
{
	class Line : public Renderable
	{
	public:
		Line(
			glm::vec2 position, 
			glm::vec2 direction, 
			float length,
			glm::vec4 color
		);

		void onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const override;

		void setDirection(glm::vec2 direction);
		void setLength(float length);

	private:
		glm::vec2 m_Direction;
		float m_Length;
	};
}
