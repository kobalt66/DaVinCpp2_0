#include "GameWindow.h"

namespace davincpp
{
	GameWindow::GameWindow(uint32_t pixelSizeX, uint32_t pixelSizeY, uint32_t bytesPerPixel) 
	  : m_Width(0),
		m_Height(0),
		m_PixelSizeX(pixelSizeX), 
		m_PixelSizeY(pixelSizeY), 
		m_BytesPerPixel(bytesPerPixel)
	{
		m_Vertices = new float[]{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,	0.5f,
			-0.5f,  0.5f,
		};

		m_Indices = new uint32_t[]{ 0, 1, 2, 2, 3, 0 };
	}

	GameWindow::~GameWindow()
	{
		delete[] m_Vertices;
		delete[] m_Indices;
	}


	void GameWindow::onSetup()
	{
		m_WindowShader = Shader(ShaderProfile(VertexAttribute(0, 2, GL_FLOAT, 0)));
		m_WindowShader.loadShader("./src/data/shader/vertex.shader", "./src/data/shader/fragment.shader");
		
		m_Mesh = Mesh<float>();
		m_Mesh.createMesh(m_Vertices, m_Indices, m_WindowShader);
	}

	void GameWindow::onClear()
	{
		if (m_FrameBuffer == nullptr) {
			return;
		}

		memset(m_FrameBuffer.get(), 0, static_cast<size_t>(m_Width * m_Height * m_BytesPerPixel + m_BytesPerPixel));
	}
	
	void GameWindow::onRender()
	{
		m_FrameTexture.updateTexture(m_FrameBuffer, m_Width, m_Height);

		m_FrameTexture.bind();
		m_WindowShader.bind();
		m_Mesh.bind();
		m_WindowShader.setUniform1i("windowBuffer", static_cast<int>(m_FrameTexture.getTextureID()));

		m_Mesh.render();
		
		m_FrameTexture.unbind();
		m_WindowShader.unbind();
		m_Mesh.unbind();
	}
	
	void GameWindow::onResize(uint32_t windowSizeX, uint32_t windowSizeY)
	{
		m_FrameBuffer.reset();
		m_FrameBuffer = std::make_shared<GLubyte[]>(windowSizeX * windowSizeY * m_BytesPerPixel + m_BytesPerPixel);
		m_Width = windowSizeX;
		m_Height = windowSizeY;
	}


	void GameWindow::setPixel(int pixelX, int pixelY, glm::vec4 color)
	{
		if (!isPixelInBoundry(pixelX, pixelY)) {
			return;
		}

		uint32_t pixelIdx = getPixelIndex(pixelX, pixelY);

		float alphaChl1 = color.a;
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
		return static_cast<size_t>(m_Width * m_Height);
	}

	inline bool GameWindow::isPixelInBoundry(int pixelX, int pixelY) const
	{
		return pixelX > 0 && pixelX < static_cast<int>(m_Width) && pixelY > 0 && pixelY < static_cast<int>(m_Height);
	}

	inline uint32_t GameWindow::getPixelIndex(int pixelX, int pixelY) const
	{
		return (pixelY * m_Width + pixelX) * m_BytesPerPixel;
	}
}
