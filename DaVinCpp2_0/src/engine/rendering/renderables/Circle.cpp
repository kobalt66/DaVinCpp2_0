#include "Circle.h"

namespace davincpp
{
	Circle::Circle(glm::vec2 position, float radius, glm::vec4 color)
		: Renderable(position, color), m_Radius(radius)
	{ }


	void Circle::onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const
	{
		if (m_Radius <= 0) {
			return;
		}

		int posX = static_cast<int>(m_Position.x);
		int posY = static_cast<int>(m_Position.y);

		int x0 = 0;
		int y0 = static_cast<int>(m_Radius);
		int d = 3 - 2 * static_cast<int>(m_Radius);

		while (y0 >= x0) {
			drawLine(frameBuffer, posX - y0, posX + y0, posY - x0);

			if (x0 > 0) {
				drawLine(frameBuffer, posX - y0, posX + y0, posY + x0);
			}

			if (d < 0) {
				d += 4 * x0++ + 6;
				continue;
			}

			if (x0 != y0) {
				drawLine(frameBuffer, posX - x0, posX + x0, posY - y0);
				drawLine(frameBuffer, posX - x0, posX + x0, posY + y0);
			}

			d += 4 * (x0++ - y0--) + 10;
		}
	}


	void Circle::drawLine(FrameBuffer& frameBuffer, int sx, int ex, int y) const
	{
		for (int x = sx; x <= ex; x++) {
			frameBuffer.setPixel(x, y, m_Color);
		}
	}
}
