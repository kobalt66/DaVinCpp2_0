#pragma once
#include <rendering/renderables/Renderable.h>

namespace davincpp
{
	class Triangle : public Renderable
	{
	public:
		Triangle(
			glm::vec2 basePosition, 
			glm::vec2 position2, 
			glm::vec2 position3, 
			glm::vec4 color
		);
		
		void onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const override;

	private:
		glm::vec2 m_Position1;
		glm::vec2 m_Position2;
		glm::vec2 m_Position3;
	};
}
