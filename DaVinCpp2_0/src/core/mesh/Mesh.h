#pragma once
#include <buffer/Vao.h>
#include <buffer/Vbo.h>
#include <buffer/Ibo.h>
#include <shader/Shader.h>

namespace davincpp
{
	template<class T> class Mesh
	{
	public:
		Mesh() = default;
		
		void createMesh(const std::vector<T>& vertices, const std::vector<uint32_t>& indices, const Shader& shader);
		void bind();
		void unbind();

		void render();

	private:
		Vao m_Vao;
		Vbo m_Vbo;
		Ibo m_Ibo;
	};
}
