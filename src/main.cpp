#if defined(_WIN32) || defined(_WIN64)

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#endif

#include "app.h"

#define WIDTH 960
#define HEIGHT 540
#define FULLSCREEN false
#define FPS 30
#define WIN_TITLE "D++"

void start_app() {
	App *app = new App;
	app->init(WIN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, FPS, FULLSCREEN);
	bool success = app->isRunning(); 
	while (app->isRunning()) {
		app->handleEvents();
		app->update();
		app->render();
	}

	if (success) app->clean();
	delete app;
}

#if defined(__linux__)
int main(int argc, char *argv[]) {
	start_app();	

	return 0;
}
#elif defined(_WIN32) || defined(_WIN64)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	start_app();

	return 0;
}
#endif
