#include "GameWindow.h"

namespace davincpp
{
	GameWindow::GameWindow(uint32_t pixelSizeX, uint32_t pixelSizeY, uint32_t bytesPerPixel)
		: m_Width(0),
		m_Height(0),
		m_FrameWidth(0),
		m_FrameHeight(0),
		m_PixelSizeX(pixelSizeX), 
		m_PixelSizeY(pixelSizeY), 
		m_BytesPerPixel(bytesPerPixel)
	{
		m_Vertices.insert(m_Vertices.begin(), {
			-1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,
			});

		m_Indices.insert(m_Indices.begin(), { 0, 1, 2, 2, 3, 0 });
	}


	void GameWindow::onSetup()
	{
		m_FrameTexture = Texture(GL_TEXTURE0);
		m_FrameTexture.createTexture();

		m_WindowShader = Shader(ShaderProfile(VertexAttribute(0, 2, GL_FLOAT, 0), VertexAttribute(1, 2, GL_FLOAT, 2)));
		m_WindowShader.loadShader("./src/data/shader/vertex.shader", "./src/data/shader/fragment.shader");
		
		m_Mesh = Mesh<float>();
		m_Mesh.createMesh(m_Vertices, m_Indices, m_WindowShader);
	}

	void GameWindow::onClear()
	{
		if (m_FrameBuffer == nullptr) {
			return;
		}

		memset(m_FrameBuffer.get(), 0, static_cast<size_t>(m_FrameWidth * m_FrameHeight * m_BytesPerPixel));
	}
	
	void GameWindow::onRender()
	{
		m_WindowShader.bind();
		m_WindowShader.setUniform1i("windowBuffer", 0);

		m_FrameTexture.bind();
		m_FrameTexture.updateTexture(m_FrameBuffer, m_FrameWidth, m_FrameHeight);
		m_FrameTexture.activate();

		m_Mesh.bind();
		m_Mesh.render();
		
		m_WindowShader.unbind();
		m_FrameTexture.unbind();
		m_Mesh.unbind();
	}
	
	void GameWindow::onResize(uint32_t windowSizeX, uint32_t windowSizeY)
	{
		m_Width = windowSizeX;
		m_Height = windowSizeY;
		m_FrameWidth = windowSizeX / m_PixelSizeX;
		m_FrameHeight = windowSizeY / m_PixelSizeY;

		m_FrameBuffer.reset();
		m_FrameBuffer = std::make_shared<GLubyte[]>(m_FrameWidth * m_FrameHeight * m_BytesPerPixel);
		m_FrameTexture.resize(m_FrameWidth, m_FrameHeight);
	}


	void GameWindow::setPixel(int pixelX, int pixelY, glm::vec4 color)
	{
		if (!isPixelInBoundry(pixelX, pixelY)) {
			return;
		}

		uint32_t pixelIdx = getPixelIndex(pixelX, pixelY);

		float alphaChl1 = color.a / 255.0f;
		float alphaChl2 = static_cast<float>(m_FrameBuffer.get()[pixelIdx + A]) / 255.0f;

		m_FrameBuffer.get()[pixelIdx + R] = static_cast<GLubyte>(alphaChl1 * color.r + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer.get()[pixelIdx + R]));
		m_FrameBuffer.get()[pixelIdx + G] = static_cast<GLubyte>(alphaChl1 * color.g + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer.get()[pixelIdx + G]));
		m_FrameBuffer.get()[pixelIdx + B] = static_cast<GLubyte>(alphaChl1 * color.b + alphaChl2 * (1.0f - alphaChl1) * static_cast<float>(m_FrameBuffer.get()[pixelIdx + B]));
		m_FrameBuffer.get()[pixelIdx + A] = static_cast<GLubyte>((alphaChl1 + alphaChl2 * (1 - alphaChl1)) * 255.0f);
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
			m_FrameBuffer.get()[pixelIdx + 0],
			m_FrameBuffer.get()[pixelIdx + 1],
			m_FrameBuffer.get()[pixelIdx + 2],
			m_FrameBuffer.get()[pixelIdx + 3]
		);
	}

	size_t GameWindow::getPixelCount() const
	{
		return static_cast<size_t>(m_FrameWidth * m_FrameHeight);
	}


	glm::uvec2 GameWindow::getPixelSize() const
	{
		return glm::uvec2(m_PixelSizeX, m_PixelSizeY);
	}

	glm::uvec2 GameWindow::getFrameSize() const
	{
		return glm::uvec2(m_FrameWidth, m_FrameHeight);
	}


	inline bool GameWindow::isPixelInBoundry(int pixelX, int pixelY) const
	{
		return pixelX >= 0 && pixelX < static_cast<int>(m_FrameWidth) && pixelY >= 0 && pixelY < static_cast<int>(m_FrameHeight);
	}

	inline uint32_t GameWindow::getPixelIndex(int pixelX, int pixelY) const
	{
		return (pixelY * m_FrameWidth + pixelX) * m_BytesPerPixel;
	}
}
