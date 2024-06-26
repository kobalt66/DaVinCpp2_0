#include "Mesh.h"
#include <DaVinCppExceptions.h>

namespace davincpp
{
	template<class T> void Mesh<T>::createMesh(const std::vector<T>& vertices, const std::vector<uint32_t>& indices, const Shader& shader)
	{
		m_Vao.generate();
		m_Vbo.generate();
		m_Ibo.generate();

		m_Vao.bind();
		m_Vbo.bind();
		m_Vbo.bindData<T>(vertices);
		
		m_Ibo.bind();
		m_Ibo.bindData(indices);
		shader.getShaderProfile().setAttributes<T>();

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
