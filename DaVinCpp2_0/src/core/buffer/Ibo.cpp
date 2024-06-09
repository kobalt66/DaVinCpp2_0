#include "Ibo.h"

namespace davincpp
{	
	Ibo::~Ibo()
	{
		unbind();
		GLCall(glDeleteBuffers(1, &m_ID));
	}


	void Ibo::generate()
	{
		GLCall(glGenBuffers(1, &m_ID));
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


	void Ibo::bindData(const std::vector<uint32_t>& data, GLenum usage)
	{
		if (!bound()) {
			bind();
		}

		m_IndicesCount = static_cast<int>(data.size());
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesCount * sizeof(uint32_t), data.data(), usage));
		m_UsageType = usage;
	}

	int Ibo::getIndicesCount()
	{
		return m_IndicesCount;
	}
}
