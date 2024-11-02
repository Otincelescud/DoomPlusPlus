#include "app.h"

#ifndef SurfaceManager_h
#define SurfaceManager_h

class SurfaceUtils {
public:
	static inline int get_w(SDL_Surface* surf);
	static inline int get_h(SDL_Surface* surf);
	static Uint32 get_pixel_from_surf(SDL_Surface* surf, std::pair<int, int>& pixel_pos);
	static void surf_pixel_map(SDL_Surface* surf,
		       		std::pair<int, int>& start_px,
		       	 	std::pair<int, int>& end_px,
		       	 	void (*func)(Uint32));

};

class Surface {
public:
	Surface(SDL_Surface* surf, std::pair<int, int>& f_pixel, std::pair<int, int>& l_pixel);
	inline int get_w();
	inline int get_h();
	Uint32 get_pixel(std::pair<int, int>& px_pos_in_tex);
	void pixel_map(std::pair<int, int>& start_px,
		       std::pair<int, int>& end_px,
		       void (*func)(Uint32));

private:
	SDL_Surface* atlas_surface;
	std::pair<int, int> first_pixel;
	std::pair<int, int> last_pixel;
};

class SurfaceManager {
public:
	void load_at_init();
	std::vector<SDL_Surface*> atlases;
	std::vector<Surface> surfaces;
};

#endif /* SurfaceManager */
