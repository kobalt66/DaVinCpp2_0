#pragma once
#include <cstdint>
#include <opengl.h>
#include <vector>

namespace davincpp
{
	class Ibo
	{
	public:
		Ibo();
		~Ibo();

		void bind();
		void unbind();
		bool bound() const;
		
		void bindData(uint32_t* data, size_t size, GLenum usage = GL_STATIC_DRAW);
		int getIndicesCount();

	private:
		uint32_t m_ID		= 0;
		int m_IndicesCount	= 0;
		bool m_Bound		= false;
		GLenum m_UsageType	= GL_STATIC_DRAW;
	};
}
