#include <iostream>
#include "src/engine/Application.h"
#include <sstream>
#include <Console.h>

int main()
{
	try {
		davincpp::Application app;
		app.onStartEngine();
		app.onLoad();

		while (!app.shouldShutdown()) {
			app.onClear();
			app.onRender();
			app.onUpdate();
		}

		app.onShutdown();
	}
	catch (std::runtime_error& exception) {
		davincpp::Console::raw(davincpp::Console::RED, exception.what());
		return 1;
	}

	return 0;
}
