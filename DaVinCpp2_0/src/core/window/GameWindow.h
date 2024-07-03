#pragma once
#include <mesh/Mesh.h>
#include <texture/Texture.h>
#include <FrameBuffer.h>
#include <gameobjects/GameObject.h>

namespace davincpp
{
	class GameWindow
	{
	public:
		GameWindow();

		void onSetup();
		void onClear();
		void onRender();
		void onUpdate();
		void onResize(uint32_t windowSizeX, uint32_t windowSizeY);
		void onMousePosition(double xpos, double ypos);

		glm::ivec2 getFrameSize() const;
		glm::ivec2 getMousePosition() const;
		FrameBuffer& getFrameBuffer();
		std::shared_ptr<GameObject> getCursor();

	private:
		void updateCursorPosition();

	private:
		uint32_t m_Width = 0, m_Height = 0;

		std::vector<float> m_Vertices;
		std::vector<uint32_t> m_Indices;

		FrameBuffer m_FrameBuffer;
		Texture m_FrameTexture;
		Mesh<float> m_Mesh;
		Shader m_WindowShader;

		std::shared_ptr<GameObject> m_Cursor;
		glm::ivec2 m_MousePosition = glm::ivec2(0);
		glm::vec4 m_CursorColor;
	};
}
