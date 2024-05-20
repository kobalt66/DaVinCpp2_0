#include "ShaderProfile.h"
#include <DaVinCppExceptions.h>

namespace davincpp
{
	template<class... Args> ShaderProfile::ShaderProfile(Args... args)
	{
		if (!(std::is_same_v<Args, VertexAttribute> && ...)) {
			Console::err("A shader profile only accepts vertex attributes!");
			throw core_error();
		}

		m_Attributes.insert(m_Attributes.begin(), { args... });

		for (const VertexAttribute & vertexAttrib : m_Attributes) {
			m_TotalSize += vertexAttrib.getUnitCount();
		}
	}


	template<class T> void ShaderProfile::setAttributes()
	{
		for (const VertexAttribute& vertexAttrib : m_Attributes) {
			vertexAttrib.setAttribute<T>(m_TotalSize);
		}
	}
}
