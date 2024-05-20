#include <iostream>
#include "src/engine/Application.h"
#include <sstream>
#include <Console.h>
#include <FileSystem.h>

int main()
{
	try {
		davincpp::Application app;
		app.onLoad();

		while (!app.shouldShutdown()) {
			app.onUpdate();
			app.onRender();
		}

		app.onShutdown();
	}
	catch (std::runtime_error& exception) {
		davincpp::Console::raw(davincpp::Console::RED, exception.what());
		return 1;
	}

	return 0;
}
