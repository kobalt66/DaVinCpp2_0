#include "Vbo.h"

namespace davincpp
{
	Vbo::~Vbo()
	{
		unbind();
		GLCall(glDeleteBuffers(1, &m_ID));
	}


	void Vbo::generate()
	{
		GLCall(glGenBuffers(1, &m_ID));
		bind();
	}

	void Vbo::bind()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		m_Bound = true;
	}

	void Vbo::unbind()
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		m_Bound = false;
	}

	bool Vbo::bound() const
	{
		return m_Bound;
	}


	template<class T> void Vbo::bindData(T* data, size_t size, GLenum usage)
	{
		if (!bound()) {
			bind();
		}

		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
		m_Usage = usage;
	}



	template void Vbo::bindData<float>(float* data, size_t size, GLenum usage);
}
