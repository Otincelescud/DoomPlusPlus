#ifndef App_hpp
#define App_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <json/json.h>

#include "world.h"
#include "surface_manager.h"

class App {
public:
	App();
	~App();

	void init(const char *title, int xpos, int ypos, unsigned int w, unsigned int h, unsigned int fps, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning();
private:
	SDL_Surface* screenSurface;
	bool running;
	unsigned int fps;
	unsigned int frame_num;
	Uint32 frame_start;
	int frame_time;
	SDL_Window *win;
};

#endif /* App_hpp */
