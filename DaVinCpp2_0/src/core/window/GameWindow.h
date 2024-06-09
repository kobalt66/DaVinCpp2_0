#pragma once
#include <mesh/Mesh.h>
#include <texture/Texture.h>

namespace davincpp
{
	class GameWindow
	{
	public:
		GameWindow() = default;
		GameWindow(uint32_t pixelSizeX, uint32_t pixelSizeY, uint32_t bytesPerPixel);

		void onSetup();
		void onClear();
		void onRender();
		void onResize(uint32_t windowSizeX, uint32_t windowSizeY);

		void setPixel(int pixelX, int pixelY, glm::vec4 color);
		void setPixelSize(glm::ivec2 pixelSize);
		glm::vec4 getPixel(int pixelX, int pixelY) const;
		size_t getPixelCount() const;

		glm::uvec2 getPixelSize() const;
		glm::uvec2 getFrameSize() const;

	private:
		inline bool isPixelInBoundry(int pixelX, int pixelY) const;
		inline uint32_t getPixelIndex(int pixelX, int pixelY) const;

	private:
		std::shared_ptr<GLubyte[]> m_FrameBuffer = nullptr;
		uint32_t m_Width = 0, m_Height = 0;
		uint32_t m_FrameWidth = 0, m_FrameHeight = 0;
		uint32_t m_PixelSizeX = 0, m_PixelSizeY = 0;
		uint32_t m_BytesPerPixel = 0;

		std::vector<float> m_Vertices;
		std::vector<uint32_t> m_Indices;

		Texture m_FrameTexture;
		Mesh<float> m_Mesh;
		Shader m_WindowShader;

		const int R = 0;
		const int G = 1;
		const int B = 2;
		const int A = 3;
	};
}
