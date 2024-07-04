#pragma once
#include <rendering/renderables/Renderable.h>

namespace davincpp
{
	class Circle : public Renderable
	{
	public:
		Circle(glm::vec2 position, float radius, glm::vec4 color, bool centerAligned);

		void onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const override;

	private:
		void drawLine(FrameBuffer& frameBuffer, std::shared_ptr<Texture2D> texture, int sx, int ex, int y, glm::vec2 surfaceScale) const;

	private:
		float m_Radius;
		bool m_CenterAligned;
	};
}
