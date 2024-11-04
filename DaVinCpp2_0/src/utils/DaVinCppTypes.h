#pragma once
#include <chrono>

namespace davincpp
{
	typedef std::chrono::system_clock		clock;
	typedef std::chrono::time_point<clock>	timestamp;
	typedef std::chrono::milliseconds		msc;
	typedef std::chrono::seconds			sec;
	typedef std::chrono::minutes			min;

	using uchar_t = unsigned char;
}
