#pragma once
#include <stdexcept>

namespace davincpp
{
	class system_error : public std::runtime_error 
	{
	public:
		explicit system_error();
	};

	class core_error : public std::runtime_error 
	{
	public:
		explicit core_error();
	};

	class glfw_error : public std::runtime_error 
	{
	public:
		explicit glfw_error();
	};

	class opengl_error : public std::runtime_error 
	{
	public:
		explicit opengl_error();
	};

	class event_error : public std::runtime_error 
	{
	public:
		explicit event_error();
	};

	class not_implemented : public std::runtime_error
	{
	public:
		explicit not_implemented(int line, const char* file);
	};

	class davincpp_error : public std::runtime_error
	{
	public:
		explicit davincpp_error(std::string_view message);
	};
}
