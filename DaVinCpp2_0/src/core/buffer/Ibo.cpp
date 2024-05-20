#include "Ibo.h"

namespace davincpp
{
	Ibo::Ibo() 
	{
		GLCall(glGenBuffers(1, &m_ID));
		bind();
	}
	
	Ibo::~Ibo()
	{
		unbind();
		GLCall(glDeleteBuffers(1, &m_ID));
	}


	void Ibo::bind()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		m_Bound = true;
	}

	void Ibo::unbind()
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		m_Bound = false;
	}

	bool Ibo::bound() const
	{
		return m_Bound;
	}


	void Ibo::bindData(uint32_t* data, size_t size, GLenum usage)
	{
		if (!bound()) {
			bind();
		}

		m_IndicesCount = static_cast<int>(size);
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesCount, data, usage));
		m_UsageType = usage;
	}

	int Ibo::getIndicesCount()
	{
		return m_IndicesCount;
	}
}
