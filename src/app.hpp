#ifndef App_hpp
#define App_hpp

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
	bool running;
	unsigned int fps;
	unsigned int frame_num;
	Uint32 frame_start;
	int frame_time;
	SDL_Window *win;
	SDL_Renderer *renderer;
};

#endif /* App_hpp */
