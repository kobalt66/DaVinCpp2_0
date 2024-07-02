#include "Square.h"
#include <rendering/TextureMapper.h>

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
		if (auto texture = gameObjectStats.m_ObjectPtr->getTexture()) {
			onRenderWithTexture(texture, gameObjectStats, frameBuffer);
			return;
		}

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


	void Square::onRenderWithTexture(std::shared_ptr<Texture2D> texture, const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const
	{
		glm::vec2 surfaceScale = texture->wrapToSurface() ? m_Scale : static_cast<glm::vec2>(texture->getTextureSize());
		glm::vec2 startPosition = m_Position;
		glm::vec2 endPosition = startPosition + surfaceScale - glm::vec2(1);

		if (m_CenterAligned) {
			startPosition -= surfaceScale / 2.0f;
			endPosition -= surfaceScale / 2.0f;
		}

		glm::ivec2 flooredStartPosition = glm::floor(startPosition);
		glm::ivec2 flooredEndPosition = glm::floor(endPosition);

		for (int y = flooredStartPosition.y; y < flooredEndPosition.y; y++) {
			for (int x = flooredStartPosition.x; x < flooredEndPosition.x; x++) {
				int textureSpaceX = x - static_cast<int>(m_Position.x);
				int textureSpaceY = y - static_cast<int>(m_Position.y);

				frameBuffer.setPixel(x, y, TextureMapper::mapTextureToSurface(texture, textureSpaceX, textureSpaceY, surfaceScale.x, surfaceScale.y));
			}
		}
	}
}
