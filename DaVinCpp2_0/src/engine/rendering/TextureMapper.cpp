#include "TextureMapper.h"

namespace davincpp
{
	glm::vec4&& TextureMapper::mapTextureToSurface(std::shared_ptr<Texture2D> texture, int pixelX, int pixelY, float width, float height)
	{
		return texture->getColorByUV(
			pixelX / (width - 1),
			pixelY / (height - 1)
		);
	}
}
