#pragma once
#include <cstdint>
#include <opengl.h>

namespace davincpp
{
	class Vao
	{
	public:
		Vao();
		~Vao();

		void bind();
		void unbind();
		bool bound() const;

	private:
		uint32_t m_ID	= 0;
		bool m_Bound	= false; 
	};
}