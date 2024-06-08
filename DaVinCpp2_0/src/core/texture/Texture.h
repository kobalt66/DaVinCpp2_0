#pragma once
#include <opengl.h>

namespace davincpp
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(uint32_t textureSlot);
		~Texture();

		void createTexture(
			GLenum wrapS = GL_CLAMP_TO_EDGE,
			GLenum wrapT = GL_CLAMP_TO_EDGE,
			GLenum minFilter = GL_NEAREST,
			GLenum maxFilter = GL_NEAREST
		);
		void resize(uint32_t textureWidth, uint32_t textureHeight);
		void activate();
		void bind();
		void unbind();

		void updateTexture(std::shared_ptr<GLubyte[]> pixelBuffer, uint32_t textureWidth, uint32_t textureHeight);
		uint32_t getTextureSlot() const;

	private:
		uint32_t m_TextureID = 0;
		uint32_t m_TextureSlot = -1;
	};
}
