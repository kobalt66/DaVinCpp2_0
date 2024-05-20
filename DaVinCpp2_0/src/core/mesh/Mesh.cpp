#include "Mesh.h"
#include <DaVinCppExceptions.h>

namespace davincpp
{
	template<class T> Mesh<T>::Mesh(T* vertices, uint32_t* indices, Shader* shader)
	{
		m_Vao.bind();
		m_Vbo.bind();
		m_Ibo.bind();
		
		m_Vbo.bindData<T>(vertices, 8);
		m_Ibo.bindData(indices, 6);
		shader->getShaderProfile().setAttributes<T>();

		m_Vao.unbind();
		m_Vbo.unbind();
		m_Ibo.unbind();
	}


	template<class T> void Mesh<T>::bind()
	{
		m_Vao.bind();
	}

	template<class T> void Mesh<T>::unbind()
	{
		m_Vao.unbind();
	}


	template<class T> void Mesh<T>::render()
	{
		if (!m_Vao.bound()) {
			Console::openglErr("Failed to render mesh because it is unbound!");
			throw opengl_error();
		}

		GLCall(glDrawElements(GL_TRIANGLES, m_Ibo.getIndicesCount(), GL_UNSIGNED_INT, nullptr));
	}



	template class Mesh<float>;
}
