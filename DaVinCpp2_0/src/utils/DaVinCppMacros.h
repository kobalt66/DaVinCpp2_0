#pragma once
#include <Console.h>

namespace davinpp
{
#define ASSERT_ENGINE_CALL(call, ctxName) \
	try { call; } \
	catch (davincpp::davincpp_error& engine_exception) { \
		Console::err("on routine call: (", ctxName, "): \n", engine_exception.what()); \
	}
}
