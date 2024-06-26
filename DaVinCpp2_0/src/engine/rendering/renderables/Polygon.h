#pragma once
#include <rendering/renderables/Triangle.h>
#include <vector>

namespace davincpp
{
	class Polygon : public Renderable
	{
	public:
		Polygon(glm::vec2 basePosition, glm::vec4 color);

		void onRender(FrameBuffer& frameBuffer) const override;

		void bakeGeometry();
		
		void addVertices(std::unique_ptr<glm::vec2[]> vertices);
		void addIndices(std::unique_ptr<uint32_t[]> indices, size_t indicesCount);

	public:
		static constexpr const int VERTICES_PER_TRIANGLE = 3;

	private:
		std::unique_ptr<glm::vec2[]> m_Vertices = nullptr;
		std::unique_ptr<uint32_t[]> m_Indices = nullptr;

		std::vector<Triangle> m_Triangles;
		size_t m_IndicesCount = 0;
	};
}
