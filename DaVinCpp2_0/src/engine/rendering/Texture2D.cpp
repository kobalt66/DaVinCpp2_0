#include "Texture2D.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppExceptions.h>
#include <DaVinCppConstants.h>
#include <Color.h>
#include <stb/stb_image.h>

namespace davincpp
{
	Texture2D::Texture2D(std::string_view filePath)
		: Component(ComponentType::TEXTURE), m_FilePath(filePath.data())
	{ }


	void Texture2D::flipTexturesH(bool flip)
	{
		stbi_set_flip_vertically_on_load(static_cast<int>(flip));
	}


	void Texture2D::onLoad()
	{
		if (!DaVinCppFileSystem::exists(m_FilePath)) {
			throw davincpp_error(Console::fmtTxt("Failed to load texture asset: The texture file at '", m_FilePath, "' doesn't exist!"));
		}

		m_TextureBuffer = std::unique_ptr<uchar_t[]>(stbi_load(m_FilePath, &m_Width, &m_Height, &m_BytesPerPixel, DESIRED_CHANNEL_COUNT));
	}


	glm::vec4&& Texture2D::getColorByUV(float x, float y) const
	{
		int u = static_cast<int>(std::floorf(x * m_Width)) % m_Width;
		int v = static_cast<int>(std::floorf(y * m_Height)) % m_Height;

		if (!validateUVCoordinates(u, v)) {
			return glm::vec4(
				static_cast<float>(m_TextureBuffer[R] / MAX_COLOR_VALUE),
				static_cast<float>(m_TextureBuffer[G] / MAX_COLOR_VALUE),
				static_cast<float>(m_TextureBuffer[B] / MAX_COLOR_VALUE),
				static_cast<float>(m_TextureBuffer[A] / MAX_COLOR_VALUE)
				);
		}

		uint32_t pixelIdx = getPixelIndex(u, v);

		return glm::vec4(
			m_TextureBuffer[pixelIdx + R],
			m_TextureBuffer[pixelIdx + G],
			m_TextureBuffer[pixelIdx + B],
			m_TextureBuffer[pixelIdx + A]
		);
	}

	glm::ivec2 Texture2D::getTextureSize() const
	{
		return glm::uvec2(m_Width, m_Height);
	}


	inline bool Texture2D::validateUVCoordinates(int u, int v) const
	{
		return u >= 0 && u < m_Width && v >= 0 && v < m_Height;
	}

	inline uint32_t Texture2D::getPixelIndex(int pixelX, int pixelY) const
	{
		return (pixelY * m_Width + pixelX) * m_BytesPerPixel;
	}
}