#pragma once
#include <rendering/renderables/Renderable.h>

namespace davincpp
{
	class Circle : public Renderable
	{
	public:
		Circle(glm::vec2 position, float radius, glm::vec4 color);

		void onRender(FrameBuffer& frameBuffer) const override;

	private:
		void drawLine(FrameBuffer& frameBuffer, int sx, int ex, int y) const;

	private:
		float m_Radius;
	};
}
