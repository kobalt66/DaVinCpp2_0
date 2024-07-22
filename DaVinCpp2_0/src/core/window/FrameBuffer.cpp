#include "FrameBuffer.h"
#include <DaVinCppConstants.h>
#include <cstring>

namespace davincpp
{
	FrameBuffer::FrameBuffer(uint32_t pixelSizeX, uint32_t pixelSizeY, uint32_t bytesPerPixel)
		: m_FrameWidth(0),
		m_FrameHeight(0),
		m_PixelSizeX(pixelSizeX),
		m_PixelSizeY(pixelSizeY),
		m_BytesPerPixel(bytesPerPixel)
	{ }


	void FrameBuffer::onResize(uint32_t windowSizeX, uint32_t windowSizeY)
	{
		m_FrameWidth = windowSizeX / m_PixelSizeX;
		m_FrameHeight = windowSizeY / m_PixelSizeY;

		m_FrameBuffer.reset();
		m_FrameBuffer = std::make_shared<GLubyte[]>(m_FrameWidth * m_FrameHeight * m_BytesPerPixel);
	}

	void FrameBuffer::onClear()
	{
		if (m_FrameBuffer == nullptr) {
			return;
		}

		memset(m_FrameBuffer.get(), 0, static_cast<size_t>(m_FrameWidth * m_FrameHeight * m_BytesPerPixel));
	}


	void FrameBuffer::setPixel(int pixelX, int pixelY, glm::vec4 color)
	{
		if (!isPixelInBoundry(pixelX, pixelY)) {
			return;
		}

		uint32_t pixelIdx = getPixelIndex(pixelX, pixelY);

		float alphaChl1 = color.a / MAX_COLOR_VALUE;
		float alphaChl2 = static_cast<float>(m_FrameBuffer.get()[pixelIdx + A]) / MAX_COLOR_VALUE;

		m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + R)] = static_cast<GLubyte>(alphaChl1 * color.r + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer.get()[pixelIdx + R]));
		m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + G)] = static_cast<GLubyte>(alphaChl1 * color.g + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer.get()[pixelIdx + G]));
		m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + B)] = static_cast<GLubyte>(alphaChl1 * color.b + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer.get()[pixelIdx + B]));
		m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + A)] = static_cast<GLubyte>((alphaChl1 + alphaChl2 * (1 - alphaChl1)) * MAX_COLOR_VALUE);
	}

	void FrameBuffer::setPixelSize(glm::ivec2 pixelSize)
	{
		m_PixelSizeX = pixelSize.x;
		m_PixelSizeY = pixelSize.y;
	}

	glm::vec4 FrameBuffer::getPixel(int pixelX, int pixelY) const
	{
		if (!isPixelInBoundry(pixelX, pixelY)) {
			return glm::vec4(0);
		}

		uint32_t pixelIdx = getPixelIndex(pixelX, pixelY);

		return glm::vec4(
			m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + R)],
			m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + G)],
			m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + B)],
			m_FrameBuffer[static_cast<ptrdiff_t>(pixelIdx + A)]
		);
	}

	size_t FrameBuffer::getPixelCount() const
	{
		return static_cast<size_t>(m_FrameWidth * m_FrameHeight);
	}


	glm::uvec2 FrameBuffer::getPixelSize() const
	{
		return glm::uvec2(m_PixelSizeX, m_PixelSizeY);
	}

	glm::uvec2 FrameBuffer::getFrameSize() const
	{
		return glm::uvec2(m_FrameWidth, m_FrameHeight);
	}

	const std::shared_ptr<GLubyte[]> FrameBuffer::getBufferPtr() const
	{
		return m_FrameBuffer;
	}


	inline bool FrameBuffer::isPixelInBoundry(int pixelX, int pixelY) const
	{
		return pixelX >= 0 && pixelX < static_cast<int>(m_FrameWidth) && pixelY >= 0 && pixelY < static_cast<int>(m_FrameHeight);
	}

	inline uint32_t FrameBuffer::getPixelIndex(int pixelX, int pixelY) const
	{
		return (pixelY * m_FrameWidth + pixelX) * m_BytesPerPixel;
	}
}
