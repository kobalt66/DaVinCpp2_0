#pragma once
#include <gameobjects/components/Component.h>
#include <DaVinCppTypes.h>
#include <opengl.h>
#include <memory>

namespace davincpp
{
	class Texture2D : public Component
	{
	public:
		Texture2D(std::string_view filePath);

		static void flipTexturesH(bool flip);

		void onLoad() override;

		glm::vec4&& getColorByUV(float x, float y) const;
		glm::ivec2 getTextureSize() const;

	private:
		inline bool validateUVCoordinates(int u, int v) const;
		inline uint32_t getPixelIndex(int pixelX, int pixelY) const;

	public:
		static constexpr const int DESIRED_CHANNEL_COUNT = 4;

	private:
		std::unique_ptr<uchar_t[]> m_TextureBuffer = nullptr;
		const char* m_FilePath = nullptr;

		int m_Width = 0, m_Height = 0;
		int m_BytesPerPixel = 0;
	};
}
