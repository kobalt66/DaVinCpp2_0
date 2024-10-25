#include "src/engine/Application.h"
#include <Console.h>

#include "DaVinCppFileSystem.h"

int main()
{
	try {
		davincpp::DaVinCppFileSystem::canWrite("/root");

		davincpp::Application app;
		app.onStartEngine();
		app.onLoad();

		while (!app.shouldShutdown()) {
			app.onClear();
			app.onRender();
			app.onUpdate();
		}

		app.onShutdown();
	} catch (std::runtime_error& exception) {
#ifdef __linux__
		davincpp::Console::shutDownNcurses();
#endif
		davincpp::Console::raw(davincpp::Console::RED, exception.what());
		davincpp::Console::raw(davincpp::Console::GRAY, "Unhandled error...");
		return 1;
	}

	return 0;
}
