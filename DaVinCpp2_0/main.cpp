#include <iostream>
#include "src/engine/Application.h"
#include <sstream>

int main()
{
	davincpp::Application app;
	app.onLoad();

	while (!app.shouldShutdown()) {
		app.onUpdate();
		app.onRender();
	}

	app.onShutdown();

	return 0;
}
