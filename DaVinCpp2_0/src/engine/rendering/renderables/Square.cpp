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


	void Square::onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const
	{
		glm::vec2 surfaceScale = m_Scale;

		std::shared_ptr<Texture2D> texture = gameObjectStats.m_ObjectPtr->getTexture();

		if (texture) {
			surfaceScale = texture->wrapToSurface() ? surfaceScale : static_cast<glm::vec2>(texture->getTextureSize());
		}

		glm::vec2 startPosition = m_Position;
		glm::vec2 endPosition = startPosition + surfaceScale;

		if (m_CenterAligned) {
			startPosition -= surfaceScale / 2.0f;
			endPosition -= surfaceScale / 2.0f;
		}

		glm::ivec2 flooredStartPosition = glm::floor(startPosition);
		glm::ivec2 flooredEndPosition = glm::floor(endPosition);

		for (int y = flooredStartPosition.y; y < flooredEndPosition.y; y++) {
			for (int x = flooredStartPosition.x; x < flooredEndPosition.x; x++) {
				frameBuffer.setPixel(x, y, texture ? mapTextureByUVCoords(texture, x, y, surfaceScale.x, surfaceScale.y) : m_Color);
			}
		}
	}


	void Square::setScale(float width, float height)
	{
		m_Width = width;
		m_Height = height;
		m_Scale = glm::vec2(width, height);
	}

	glm::vec2 Square::getScale() const
	{
		return m_Scale;
	}
}
