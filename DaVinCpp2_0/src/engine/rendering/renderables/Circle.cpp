#include "Circle.h"

namespace davincpp
{
	Circle::Circle(glm::vec2 position, float radius, glm::vec4 color, bool centerAligned)
		: Renderable(position, color), m_Radius(radius), m_CenterAligned(centerAligned)
	{ }


	void Circle::onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const
	{
		glm::vec2 surfaceScale = glm::vec2(m_Radius * 2.0f);

		std::shared_ptr<Texture2D> texture = gameObjectStats.m_ObjectPtr->getTexture();

		if (m_Radius <= 0) {
			return;
		}

		int posX = 0;
		int posY = 0;

		if (m_CenterAligned) {
			posX = static_cast<int>(m_Position.x);
			posY = static_cast<int>(m_Position.y);
		}
		else {
			posX = static_cast<int>(m_Position.x + m_Radius - 1);
			posY = static_cast<int>(m_Position.y + m_Radius - 1);
		}

		int x0 = 0;
		int y0 = static_cast<int>(m_Radius);
		int d = 3 - 2 * static_cast<int>(m_Radius);

		while (y0 >= x0) {
			drawLine(frameBuffer, texture, posX - y0, posX + y0, posY - x0, surfaceScale);

			if (x0 > 0) {
				drawLine(frameBuffer, texture, posX - y0, posX + y0, posY + x0, surfaceScale);
			}

			if (d < 0) {
				d += 4 * x0++ + 6;
				continue;
			}

			if (x0 != y0) {
				drawLine(frameBuffer, texture, posX - x0, posX + x0, posY - y0, surfaceScale);
				drawLine(frameBuffer, texture, posX - x0, posX + x0, posY + y0, surfaceScale);
			}

			d += 4 * (x0++ - y0--) + 10;
		}
	}


	void Circle::drawLine(FrameBuffer& frameBuffer, std::shared_ptr<Texture2D> texture, int sx, int ex, int y, glm::vec2 surfaceScale) const
	{
		for (int x = sx; x <= ex; x++) {
			int textureOffsetX = m_CenterAligned ? x + static_cast<int>(m_Radius) - 1 : x;
			int textureOffsetY = m_CenterAligned ? y + static_cast<int>(m_Radius) - 1 : y;

			frameBuffer.setPixel(x, y, texture ? mapTextureByUVCoords(texture, textureOffsetX, textureOffsetY, surfaceScale.x, surfaceScale.y) : m_Color);
		}
	}
}
