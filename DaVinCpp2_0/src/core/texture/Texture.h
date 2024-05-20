#pragma once
#include <opengl.h>

namespace davincpp
{
	class Texture
	{
	public:
		Texture(
			GLenum wrapS = GL_CLAMP_TO_EDGE, 
			GLenum wrapT = GL_CLAMP_TO_EDGE, 
			GLenum minFilter = GL_NEAREST, 
			GLenum maxFilter = GL_NEAREST
		);
		~Texture();

		void bind();
		void unbind();

		void updateTexture(GLbyte* pixelBuffer, uint32_t textureWidth, uint32_t textureHeight);
		uint32_t getTextureID() const;

	private:
		uint32_t m_TextureID;
	};
}
