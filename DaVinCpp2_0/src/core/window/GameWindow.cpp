#include "GameWindow.h"

namespace davincpp
{
	GameWindow::GameWindow(uint32_t pixelSizeX, uint32_t pixelSizeY, uint32_t bytesPerPixel)
		: m_PixelSizeX(pixelSizeX), m_PixelSizeY(pixelSizeY), m_BytesPerPixel(bytesPerPixel)
	{
		m_Vertices = new float[]{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,	0.5f,
			-0.5f,  0.5f,
		};

		m_Indices = new uint32_t[]{ 0, 1, 2, 2, 3, 0 };

		m_WindowShader = std::make_unique<Shader>(VertexAttribute(0, 2, GL_FLOAT, 0));
		m_Mesh = Mesh<float>(m_Vertices, m_Indices, m_WindowShader.get());
	}

	GameWindow::~GameWindow()
	{
		delete[] m_FrameBuffer;
		delete[] m_Vertices;
		delete[] m_Indices;
	}


	void GameWindow::onClear()
	{
		memset(m_FrameBuffer, 0, m_Width * m_Height * m_BytesPerPixel + m_BytesPerPixel);
	}
	
	void GameWindow::onRender()
	{
		m_FrameTexture.updateTexture(m_FrameBuffer, m_Width, m_Height);

		m_Mesh.bind();
		m_WindowShader->bind();
		m_WindowShader->setUniform1i("windowBuffer", static_cast<int>(m_FrameTexture.getTextureID()));

		m_Mesh.render();
		
		m_WindowShader->unbind();
		m_Mesh.unbind();
	}
	
	void GameWindow::onResize(uint32_t windowSizeX, uint32_t windowSizeY)
	{
		
	}


	void GameWindow::setPixel(int pixelX, int pixelY, glm::vec4 color)
	{
		if (!isPixelInBoundry(pixelX, pixelY)) {
			return;
		}

		uint32_t pixelIdx = getPixelIndex(pixelX, pixelY);

		float alphaChl1 = color.a;
		float alphaChl2 = static_cast<float>(m_FrameBuffer[pixelIdx + A]) / 255.0f;

		m_FrameBuffer[pixelIdx + R] = static_cast<GLbyte>(alphaChl1 * color.r + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer[pixelIdx + R]));
		m_FrameBuffer[pixelIdx + G] = static_cast<GLbyte>(alphaChl1 * color.g + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer[pixelIdx + G]));
		m_FrameBuffer[pixelIdx + B] = static_cast<GLbyte>(alphaChl1 * color.b + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer[pixelIdx + B]));
		m_FrameBuffer[pixelIdx + A] = static_cast<GLbyte>((alphaChl1 + alphaChl2 * (1 - alphaChl1)) * 255.0f);
	}

	void GameWindow::setPixelSize(glm::ivec2 pixelSize)
	{
		m_PixelSizeX = pixelSize.x;
		m_PixelSizeY = pixelSize.y;
	}

	glm::vec4 GameWindow::getPixel(int pixelX, int pixelY) const
	{
		if (!isPixelInBoundry(pixelX, pixelY)) {
			return glm::vec4(0);
		}

		uint32_t pixelIdx = getPixelIndex(pixelX, pixelY);

		return glm::vec4(
			m_FrameBuffer[pixelIdx + 0],
			m_FrameBuffer[pixelIdx + 1],
			m_FrameBuffer[pixelIdx + 2],
			m_FrameBuffer[pixelIdx + 3]
		);
	}

	size_t GameWindow::getPixelCount() const
	{
		return static_cast<size_t>(m_Width * m_Height);
	}

	inline bool GameWindow::isPixelInBoundry(int pixelX, int pixelY) const
	{
		return pixelX > 0 && pixelX < m_Width && pixelY > 0 && pixelY < m_Height;
	}

	inline uint32_t GameWindow::getPixelIndex(int pixelX, int pixelY) const
	{
		return (pixelY * m_Width + pixelX) * m_BytesPerPixel;
	}
}
