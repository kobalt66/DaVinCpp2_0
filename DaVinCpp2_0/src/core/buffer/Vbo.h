#pragma once
#include <cstdint>
#include <opengl.h>
#include <vector>

namespace davincpp
{
	class Vbo
	{
	public:
		Vbo() = default;
		~Vbo();

		void generate();
		void bind();
		void unbind();
		bool bound() const;

		template<class T> void bindData(T* data, size_t size, GLenum usage = GL_STATIC_DRAW);

	private:
		uint32_t m_ID	= 0;
		bool m_Bound	= false;
		GLenum m_Usage	= GL_STATIC_DRAW;
	};
}
