#include "Polygon.h"

namespace davincpp
{
	Polygon::Polygon(glm::vec2 basePosition, glm::vec4 color)
		: Renderable(basePosition, color)
	{ }


	void Polygon::onRender(FrameBuffer& frameBuffer) const
	{
		for (const Triangle& triangle : m_Triangles) {
			triangle.onRender(frameBuffer);
		}
	}


	void Polygon::bakeGeometry()
	{
		int numberOfTirangles = static_cast<int>(m_IndicesCount / VERTICES_PER_TRIANGLE);

		for (int i = 0; i < numberOfTirangles; i++) {
			glm::vec2 vertex0 = *(m_Vertices.get() + i * VERTICES_PER_TRIANGLE + 0) + m_Position;
			glm::vec2 vertex1 = *(m_Vertices.get() + i * VERTICES_PER_TRIANGLE + 1) + m_Position;
			glm::vec2 vertex2 = *(m_Vertices.get() + i * VERTICES_PER_TRIANGLE + 2) + m_Position;

			m_Triangles.emplace_back(Triangle(vertex0, vertex1, vertex2, m_Color));
		}
	}


	void Polygon::addVertices(std::unique_ptr<glm::vec2[]> vertices)
	{
		m_Vertices = std::move(vertices);
	}

	void Polygon::addIndices(std::unique_ptr<uint32_t[]> indices, size_t indicesCount)
	{
		m_Indices = std::move(indices);
		m_IndicesCount = indicesCount;
	}
}
