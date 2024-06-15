#pragma once
#include <mesh/Mesh.h>
#include <texture/Texture.h>
#include <FrameBuffer.h>

namespace davincpp
{
	class GameWindow
	{
	public:
		GameWindow();

		void onSetup();
		void onClear();
		void onRender();
		void onResize(uint32_t windowSizeX, uint32_t windowSizeY);
		void onMousePosition(double xpos, double ypos);

		glm::ivec2 getMousePosition() const;

	private:
		uint32_t m_Width = 0, m_Height = 0;

		std::vector<float> m_Vertices;
		std::vector<uint32_t> m_Indices;

		FrameBuffer m_FrameBuffer;
		Texture m_FrameTexture;
		Mesh<float> m_Mesh;
		Shader m_WindowShader;

		glm::ivec2 m_MousePosition = glm::ivec2(0);
	};
}
