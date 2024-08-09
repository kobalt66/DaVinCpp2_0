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
