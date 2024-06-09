#pragma once
#include <cstdint>
#include <opengl.h>
#include "ShaderProfile.h"
#include <unordered_map>

namespace davincpp
{
	class Shader
	{
	public:
		Shader() = default;
		Shader(ShaderProfile&& profile);
		~Shader();

		void loadShader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath);

		void bind();
		void unbind();

		template<class T> void setup();
		const ShaderProfile& getShaderProfile() const;

		void setUniform1i(std::string_view uniform, int integer);

	private:
		int getUniformLocation(std::string_view uniform);

		uint32_t compileShader(const char* shaderCode, GLenum shaderType);
		void linkShader(uint32_t vertexShaderID, uint32_t fragmentShaderID);
		void finalizeShader(uint32_t vertexShaderID, uint32_t fragmentShaderID);

	private:
		std::unordered_map<std::string_view, int> m_UniformLocationCache;

		uint32_t m_ProgramID = 0;
		ShaderProfile m_Profile;
	};
}
