#include "Texture.h"
#include <DaVinCppConstants.h>

namespace davincpp
{
	Texture::Texture(uint32_t textureSlot)
		: m_TextureSlot(textureSlot)
	{ }

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_TextureID));
	}


	void Texture::createTexture(
		GLenum wrapS,
		GLenum wrapT,
		GLenum minFilter,
		GLenum maxFilter
	)
	{
		GLCall(glGenTextures(1, &m_TextureID));
		bind();

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT));

		unbind();
	}

	void Texture::resize(glm::uvec2 textureSize)
	{
		if (textureSize.x < MIN_FRAMEBUFFER_SIZEX || textureSize.y < MIN_FRAMEBUFFER_SIZEY) {
			return;
		}

		bind();
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize.x, textureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		unbind();
	}

	void Texture::activate()
	{
		GLCall(glActiveTexture(m_TextureSlot));
	}

	void Texture::bind()
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}
	
	void Texture::unbind()
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}


	void Texture::updateTexture(const std::shared_ptr<GLubyte[]> pixelBuffer, glm::uvec2 textureSize)
	{
		GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureSize.x, textureSize.y, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer.get()));
	}

	uint32_t Texture::getTextureSlot() const
	{
		return m_TextureSlot;
	}
}
