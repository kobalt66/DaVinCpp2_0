#include "Line.h"

namespace davincpp
{
	Line::Line(
		glm::vec2 position,
		glm::vec2 direction,
		float length,
		glm::vec4 color
	) 
		: Renderable(position, color),
		m_Direction(direction),
		m_Length(length)
	{ }


	void Line::onRender(FrameBuffer& frameBuffer) const
	{
		glm::ivec2 pos1 = (glm::ivec2)m_Position;
		glm::ivec2 pos2 = (glm::ivec2)(m_Position + glm::normalize(m_Direction) * m_Length);
	
		int dx = abs(pos2.x - pos1.x);
		int dy = abs(pos2.y - pos1.y);
		int sx = (pos1.x < pos2.x) ? 1 : -1;
		int sy = (pos1.y < pos2.y) ? 1 : -1;
		int err = dx - dy;

		while (true) {
			frameBuffer.setPixel(pos1.x, pos1.y, m_Color);

			if (pos1.x == pos2.x && pos1.y == pos2.y) break;

			int e2 = 2 * err;

			if (e2 > -dy) {
				err -= dy;
				pos1.x += sx;
			}

			if (e2 < dx) {
				err += dx;
				pos1.y += sy;
			}
		}
	}


	void Line::setDirection(glm::vec2 direction)
	{
		m_Direction = direction;
	}

	void Line::setLength(float length)
	{
		m_Length = length;
	}
}
