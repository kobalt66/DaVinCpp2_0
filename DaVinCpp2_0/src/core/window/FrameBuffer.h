#pragma once
#include <opengl.h>

namespace davincpp
{
	class FrameBuffer
	{
	public:
		FrameBuffer() = default;
		FrameBuffer(uint32_t pixelSizeX, uint32_t pixelSizeY, uint32_t bytesPerPixel);

		void onResize(uint32_t windowSizeX, uint32_t windowSizeY);
		void onClear();

		void setPixel(int pixelX, int pixelY, glm::vec4 color);
		void setPixelSize(glm::ivec2 pixelSize);
		glm::vec4&& getPixel(int pixelX, int pixelY) const;
		size_t getPixelCount() const;

		glm::uvec2 getPixelSize() const;
		glm::uvec2 getFrameSize() const;
		const std::shared_ptr<GLubyte[]> getBufferPtr() const;

	private:
		inline bool isPixelInBoundry(int pixelX, int pixelY) const;
		inline uint32_t getPixelIndex(int pixelX, int pixelY) const;

	private:
		std::shared_ptr<GLubyte[]> m_FrameBuffer = nullptr;
		uint32_t m_FrameWidth = 0, m_FrameHeight = 0;
		uint32_t m_PixelSizeX = 0, m_PixelSizeY = 0;
		uint32_t m_BytesPerPixel = 0;
	};
}
