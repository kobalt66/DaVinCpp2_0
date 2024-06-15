#pragma once
#include <stdexcept>
#include <format>

namespace davincpp
{
	class system_error : public std::runtime_error 
	{
	public:
		explicit system_error() : std::runtime_error("[SYS] fatal error") {}
	};

	class core_error : public std::runtime_error 
	{
	public:
		explicit core_error() : std::runtime_error("[CORE] fatal error") {}
	};

	class glfw_error : public std::runtime_error 
	{
	public:
		explicit glfw_error() : std::runtime_error("[GLFW] fatal error") {}
	};

	class opengl_error : public std::runtime_error 
	{
	public:
		explicit opengl_error() : std::runtime_error("[OpenGL] fatal error") {}
	};

	class event_error : public std::runtime_error 
	{
	public:
		explicit event_error() : std::runtime_error("[Event] fatal error") {}
	};

	class not_implemented : public std::runtime_error
	{
	public:
		explicit not_implemented(int line, const char* file) : std::runtime_error(std::format("(file: {}, line: {}) function is not implemented!", file, line).c_str()) {}
	};
}
