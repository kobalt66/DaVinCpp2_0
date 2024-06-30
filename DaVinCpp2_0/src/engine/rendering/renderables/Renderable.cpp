#include "Renderable.h"
#include <DaVinCppExceptions.h>

namespace davincpp
{
	Renderable::Renderable(glm::vec2 position, glm::vec4 color)
		: Component(ComponentType::SURFACE), m_Position(position), m_Color(color)
	{ }


	void Renderable::onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const
	{
		throw not_implemented(__LINE__, __FILE__);
	}
	

	glm::vec2 Renderable::getPosition()
	{
		return m_Position;
	}
	
	void Renderable::setPosition(glm::vec2 position)
	{
		m_Position = position;
	}
}
