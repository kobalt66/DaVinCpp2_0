#include "VertexAttribute.h"

namespace davincpp
{
	VertexAttribute::VertexAttribute(int index, int unitCount, GLenum type, int offset, bool normalized)
		: m_Index(index), m_UnitCount(unitCount), m_Type(type), m_Offset(offset), m_Normalized(normalized)
	{ }


	template<class T> void VertexAttribute::setAttribute(int totalSize) const
	{
		GLCall(glVertexAttribPointer(m_Index, m_UnitCount, m_Type, m_Normalized, static_cast<GLsizei>(totalSize * sizeof(T)), (void*)(m_Offset * sizeof(T))));
		GLCall(glEnableVertexAttribArray(m_Index));
	}

	int VertexAttribute::getUnitCount() const
	{
		return m_UnitCount;
	}



	template void VertexAttribute::setAttribute<float>(int totalSize) const;
}
