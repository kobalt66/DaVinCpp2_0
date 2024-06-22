#include "Square.h"

namespace davincpp
{
	Square::Square(
		glm::vec2 position,
		glm::vec4 color,
		float width,
		float height,
		bool centerAligned
	)
		: Renderable(position, color),
		m_Width(width),
		m_Height(height),
		m_Scale(width, height),
		m_CenterAligned(centerAligned)
	{ }


	void Square::onRender(FrameBuffer& frameBuffer) const
	{
		glm::vec2 startPosition = m_Position;
		glm::vec2 endPosition = startPosition + m_Scale;

		if (m_CenterAligned) {
			startPosition -= m_Scale / 2.0f;
			endPosition -= m_Scale / 2.0f;
		}

		glm::ivec2 flooredStartPosition = glm::floor(startPosition);
		glm::ivec2 flooredEndPosition = glm::floor(endPosition);

		for (int y = flooredStartPosition.y; y < flooredEndPosition.y; y++) {
			for (int x = flooredStartPosition.x; x < flooredEndPosition.x; x++) {
				frameBuffer.setPixel(x, y, m_Color);
			}
		}
	}


	void Square::setScale(float width, float height)
	{
		m_Width = width;
		m_Height = height;
		m_Scale = glm::vec2(width, height);
	}
}
