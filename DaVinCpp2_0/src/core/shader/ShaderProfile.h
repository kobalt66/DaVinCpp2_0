#pragma once
#include "VertexAttribute.h"
#include <DaVinCppExceptions.h>
#include <vector>

namespace davincpp
{
	class ShaderProfile
	{
	public:
		template<class... Args> ShaderProfile(Args... args)
		{
			if (!(std::is_same_v<Args, VertexAttribute> && ...)) {
				Console::err("A shader profile only accepts vertex attributes!");
				throw core_error();
			}

			m_Attributes.insert(m_Attributes.begin(), { args... });

			for (const VertexAttribute& vertexAttrib : m_Attributes) {
				m_TotalSize += vertexAttrib.getUnitCount();
			}
		}

		template<class T> void setAttributes();

	private:
		std::vector<VertexAttribute> m_Attributes;
		int m_TotalSize	= 0;
	};
}
