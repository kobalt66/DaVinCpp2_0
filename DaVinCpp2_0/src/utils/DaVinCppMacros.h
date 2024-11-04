#pragma once
#include <Console.h>

namespace davinpp
{
#define ASSERT_ENGINE_CALL(call, ctxName) \
	try { call; } \
	catch (davincpp_error& error) { \
		Console::err("on routine call: (", ctxName, "): \n", error.what()); \
	}

#define ASSERT_LETHAL_ENGINE_CALL(call, ctxName) \
	try { call; } \
	catch (davincpp_error& error) { \
		Console::err("on routine call: (", ctxName, "): \n", error.what()); \
		exit(1); \
	}
}

#if !defined(NDEBUG) && DEBUG_BREAK_POINTS == 1 // Debug mode
	#ifdef _MSC_VER
		#define DEBUG_BREAK __debugbreak()
	#else
		#include <csignal>
		#define DEBUG_BREAK raise(SIGTRAP)
	#endif
#else  // Release mode
	#define DEBUG_BREAK ((void)0)  // Do nothing in release
#endif
