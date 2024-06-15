#include "GameWindow.h"

namespace davincpp
{
	GameWindow::GameWindow()
		: m_Width(0),
		m_Height(0),
		m_FrameBuffer(4, 4, 4)
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
		m_FrameBuffer.onClear();
	}
	
	void GameWindow::onRender()
	{
		m_FrameBuffer.setPixel(m_MousePosition.x, m_MousePosition.y, glm::vec4(58, 252, 161, 255));

		m_WindowShader.bind();
		m_WindowShader.setUniform1i("windowBuffer", 0);

		m_FrameTexture.bind();
		m_FrameTexture.updateTexture(m_FrameBuffer.getBufferPtr(), m_FrameBuffer.getFrameSize());
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

		m_FrameBuffer.onResize(windowSizeX, windowSizeY);
		m_FrameTexture.resize(m_FrameBuffer.getFrameSize());
	}

	void GameWindow::onMousePosition(double xpos, double ypos)
	{
		m_MousePosition.x = static_cast<int>(xpos / m_FrameBuffer.getPixelSize().x);
		m_MousePosition.y = m_FrameBuffer.getFrameSize().y - static_cast<int>(ypos / m_FrameBuffer.getPixelSize().y) - 1;
	}


	glm::ivec2 GameWindow::getFrameSize() const
	{
		return m_FrameBuffer.getFrameSize();
	}

	glm::ivec2 GameWindow::getMousePosition() const
	{
		return m_MousePosition;
	}

	FrameBuffer& GameWindow::getFrameBuffer()
	{
		return m_FrameBuffer;
	}
}
