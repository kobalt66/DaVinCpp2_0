#pragma once
#include <rendering/renderables/Renderable.h>

namespace davincpp
{
	class Square : public Renderable
	{
	public:
		Square(
			glm::vec2 position,
			glm::vec4 color,
			float width, 
			float height, 
			bool centerAligned
		);

		void onRender(const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const override;

		void setScale(float width, float height);
		glm::vec2 getScale() const;

	private:
		void onRenderWithTexture(std::shared_ptr<Texture2D> texture, const GameObjectStats& gameObjectStats, FrameBuffer& frameBuffer) const override;

	private:
		float m_Width, m_Height;
		glm::vec2 m_Scale;
		bool m_CenterAligned;
	};
}
