#pragma once
#include <opengl.h>

namespace davincpp
{
	class VertexAttribute
	{
	public:
		VertexAttribute(int index, int unitCount, GLenum type, int offset, bool normalized = false);

		template<class T> void setAttribute(int totalSize) const;
		int getUnitCount() const;

	private:
		int m_Index;
		int m_UnitCount;
		GLenum m_Type;
		int m_Offset;
		bool m_Normalized;
	};
}
