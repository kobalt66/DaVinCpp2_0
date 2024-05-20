#include "Vao.h"

namespace davincpp
{
	Vao::Vao()
	{
		GLCall(glGenVertexArrays(1, &m_ID));
		bind();
	}

	Vao::~Vao()
	{
		unbind();
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}


	void Vao::bind()
	{
		GLCall(glBindVertexArray(m_ID));
		m_Bound = true;
	}

	void Vao::unbind()
	{
		GLCall(glBindVertexArray(0));
		m_Bound = false;
	}

	bool Vao::bound() const
	{
		return m_Bound;
	}
}
