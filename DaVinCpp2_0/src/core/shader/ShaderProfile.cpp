#include "ShaderProfile.h"

namespace davincpp
{
	template<class T> void ShaderProfile::setAttributes() const
	{
		for (const VertexAttribute& vertexAttrib : m_Attributes) {
			vertexAttrib.setAttribute<T>(m_TotalSize);
		}
	}



	template void ShaderProfile::setAttributes<float>() const;
}
