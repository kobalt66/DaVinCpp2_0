#include <iostream>
#include "src/engine/Application.h"

int main()
{
	Application app;
	app.onLoad();
	
	while (!app.shouldShutdown()) {
		app.onUpdate();
		app.onRender();
	}

	app.onShutdown();

	return 0;
}
