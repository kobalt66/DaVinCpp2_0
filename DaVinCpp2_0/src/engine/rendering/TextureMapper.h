#pragma once
#include <opengl.h>
#include <rendering/Texture2D.h>

namespace davincpp
{
	class TextureMapper
	{
	public:
		static glm::vec4&& mapTextureToSurface(const Texture2D& texture, int x, int y, float width, float height);
	};
}
