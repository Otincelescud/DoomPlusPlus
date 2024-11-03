#include "app.h"

#ifndef Graphics_h
#define Graphics_h

class Renderer {
public:
	void render();

private:
	void init(WorldMap *world_map, float *player_rotation, SDL_Surface *win_surf);
	Uint32 getColorInfoFromWorld(pair<int, int>& pixel_pos);
	Uint32 getPixel(pair<int, int>& pixel_pos);
	void setPixel(pair<int, int>& pixel_pos, Uint32 pixel_val);
	void projectSurface(pair<int, int, int>& local_pos, pair<int, int, int>& local_rotation, pair<int, int, int>& local_scale);

	WorldMap* worldMap;
	float* playerState;
	SDL_Surface* winSurf;
};

#endif /* Graphics_h */
