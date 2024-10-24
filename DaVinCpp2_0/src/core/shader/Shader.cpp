#include "Shader.h"
#include <DaVinCppFileSystem.h>
#include <DaVinCppExceptions.h>

namespace davincpp
{
	Shader::Shader(ShaderProfile&& profile)
		: m_Profile(profile)
	{ }

	Shader::~Shader()
	{
		unbind();
		GLCall(glDeleteProgram(m_ProgramID));
	}


	void Shader::loadShader(std::string_view vertexShaderPath, std::string_view fragmentShaderPath)
	{
		GLCall(m_ProgramID = glCreateProgram());
		std::string vertexShaderCode = DaVinCppFileSystem::readFile(vertexShaderPath);
		std::string fragmentShaderCode = DaVinCppFileSystem::readFile(fragmentShaderPath);

		int vertexShaderID = compileShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
		int fragmentShaderID = compileShader(fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);

		linkShader(vertexShaderID, fragmentShaderID);
		finalizeShader(vertexShaderID, fragmentShaderID);
	}


	void Shader::bind() const
	{
		GLCall(glUseProgram(m_ProgramID));
	}

	void Shader::unbind()
	{
		GLCall(glUseProgram(0));
	}


	template<class T> void Shader::setup()
	{
		m_Profile.setAttributes<T>();
	}

	const ShaderProfile& Shader::getShaderProfile() const
	{
		return m_Profile;
	}


	void Shader::setUniform1i(std::string_view uniform, int integer)
	{
		int location = getUniformLocation(uniform);
		GLCall(glUniform1i(location, integer));
	}

	int Shader::getUniformLocation(std::string_view uniform)
	{
		if (m_UniformLocationCache.find(uniform) != m_UniformLocationCache.end()) {
			return m_UniformLocationCache.at(uniform);
		}

		int location = glGetUniformLocation(m_ProgramID, uniform.data());

		if (location == -1) {
			Console::err("The uniform ", uniform, " does not exit");
			throw opengl_error();
		}

		m_UniformLocationCache[uniform] = location;
		return location;
	}


	uint32_t Shader::compileShader(const char* shaderCode, GLenum shaderType)
	{
		uint32_t shaderId = glCreateShader(shaderType);
		GLCall(glShaderSource(shaderId, 1, &shaderCode, nullptr));
		GLCall(glCompileShader(shaderId));

		int result, length;
		GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));

		if (result == GL_TRUE) {
			return shaderId;
		}

		GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));

#ifdef _WIN32
		char* message = static_cast<char*>(_malloca(length * sizeof(char)));
#else
		char* message = static_cast<char*>(malloc(length * sizeof(char)));
#endif
		GLCall(glGetShaderInfoLog(shaderId, length, &length, message));

		const char* shaderTypeStr =
			shaderType == GL_VERTEX_SHADER ?
			"vertex"	:
			shaderType == GL_FRAGMENT_SHADER ?
			"fragment"	: "UNKNOWN";

		Console::openglErr("Failed to compile ", shaderTypeStr, " shader!");
		Console::newline();
		Console::err(message);
		throw opengl_error();
	}

	void Shader::linkShader(uint32_t vertexShaderID, uint32_t fragmentShaderID) const
	{
		GLCall(glAttachShader(m_ProgramID, vertexShaderID));
		GLCall(glAttachShader(m_ProgramID, fragmentShaderID));
		GLCall(glLinkProgram(m_ProgramID));

		int linkStatus, length;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == GL_TRUE) {
			return;
		}

		GLCall(glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length));

#ifdef _WIN32
		char* message = static_cast<char*>(_malloca(length * sizeof(char)));
#else
		char* message = static_cast<char*>(malloc(length * sizeof(char)));
#endif
		GLCall(glGetProgramInfoLog(m_ProgramID, length, &length, message));

		Console::openglErr("Failed to link shader program!");
		Console::newline();
		Console::err(message);
		throw opengl_error();
	}

	void Shader::finalizeShader(uint32_t vertexShaderID, uint32_t fragmentShaderID) const
	{
		GLCall(glValidateProgram(m_ProgramID));
		GLCall(glDeleteShader(vertexShaderID));
		GLCall(glDeleteShader(fragmentShaderID));
	}
}
