#include "app.hpp"

App::App() {}
App::~App() {}

void App::init(const char *title, int xpos, int ypos, unsigned int w, unsigned int h, unsigned int window_fps,  bool fullscreen) {
	running = false;
	int flags = 0;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Can't initialise SDL2: " << SDL_GetError() << '\n';
		return;
	}

	// Init SDL_image module
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		SDL_Log("Can't initialise SDL2_image: %s", SDL_GetError());
		SDL_Quit();
		return;
	}

	SDL_DisplayMode displayMode;
        if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
		SDL_Log("Can't get display mode: %s", SDL_GetError());
		IMG_Quit();
		SDL_Quit();
		return;
        }

	// Init window dimensions

	if (!fullscreen && (w > displayMode.w || h > displayMode.h)) {
		SDL_Log("Failed to set window width and height: Invalid dimensions");
		IMG_Quit();
		SDL_Quit();
		return;
	}

	// Set vars for fullscreen

	if (fullscreen) {
		w = displayMode.w;
		h = displayMode.h;
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}

	// Create window
	
	win = SDL_CreateWindow(title, xpos, ypos, w, h, flags);
	if (!win) {
		SDL_Log("Can't create main window: %s", SDL_GetError());
		IMG_Quit();
		SDL_Quit();
		return;
	}

	// Create renderer
	
	// Doom didn't need hardware acceleration so neither do I
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer) {
		SDL_Log("Can't create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(win);
		IMG_Quit();
		SDL_Quit();
		return;
	}

	SDL_SetRenderDrawColor(renderer, 127, 30, 127, 255);
	fps = window_fps;
	frame_num = 1;
	running = true;

}

bool App::isRunning() { return running; }

void App::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: running = false; break; // Exit if window is closed
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: running = false; break; // Exit if ESC is pressed
			}
			break;
		}
	}
}

void App::update() {}
void App::render() {
	SDL_RenderClear(renderer);

	// Render Stuff
	//
	frame_time = SDL_GetTicks() - frame_start;
	if (!(frame_time*fps >= 1000 || frame_num == 1)) SDL_Delay(1000.0 / fps - frame_time);

	SDL_RenderPresent(renderer);

	frame_start = SDL_GetTicks();
	frame_num++;
}

void App::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
}
