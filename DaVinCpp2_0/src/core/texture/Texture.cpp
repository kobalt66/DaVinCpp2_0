#include "Texture.h"

namespace davincpp
{
	Texture::Texture(
		GLenum wrapS,
		GLenum wrapT,
		GLenum minFilter,
		GLenum maxFilter
	)
	{
		GLCall(glGenTextures(1, &m_TextureID));
		bind();

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT));

		unbind();
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_TextureID));
	}


	void Texture::bind()
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}
	
	void Texture::unbind()
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}


	void Texture::updateTexture(GLbyte* pixelBuffer, uint32_t textureWidth, uint32_t textureHeight)
	{
		bind();
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<size_t>(textureWidth), static_cast<size_t>(textureHeight), 0, GL_RGBA, GL_UNSIGNED_INT, pixelBuffer));
		unbind();
	}

	uint32_t Texture::getTextureID() const
	{
		return m_TextureID;
	}
}
