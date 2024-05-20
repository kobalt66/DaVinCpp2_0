#pragma once
#include "VertexAttribute.h"
#include <vector>

namespace davincpp
{
	class ShaderProfile
	{
	public:
		template<class... Args> ShaderProfile(Args... args);

		template<class T> void setAttributes();

	private:
		std::vector<VertexAttribute> m_Attributes;
		int m_TotalSize	= 0;
	};
}
