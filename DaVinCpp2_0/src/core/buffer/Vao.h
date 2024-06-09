#pragma once
#include <cstdint>
#include <opengl.h>

namespace davincpp
{
	class Vao
	{
	public:
		Vao() = default;
		~Vao();

		void generate();
		void bind();
		void unbind();
		bool bound() const;

	private:
		uint32_t m_ID	= 0;
		bool m_Bound	= false; 
	};
}