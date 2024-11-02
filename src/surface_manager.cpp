#include "surface_manager.h"

// SurfaceUtils

inline int SurfaceUtils::get_w(SDL_Surface* surf) { return surf->w; }
inline int SurfaceUtils::get_h(SDL_Surface* surf) { return surf->h; }

Uint32 SurfaceUtils::get_pixel_from_surf(SDL_Surface* surf, std::pair<int, int>& pixel_pos) {
	return ((Uint32*)surf->pixels)[surf->w * pixel_pos.second + pixel_pos.first];
}

void SurfaceUtils::surf_pixel_map(SDL_Surface* surf,
				std::pair<int, int>& start_px, 
	       			std::pair<int ,int>& end_px,
	       			void (*func)(Uint32))
{
	Uint32* pixels = (Uint32*)surf->pixels;
	int w = surf->w;
	int first_px_on_row = w * start_px.second + start_px.first;
	int last_px_on_row = w * start_px.second + end_px.first;
	int last_px_on_last_row = w * end_px.second + end_px.first;
	
	while (first_px_on_row <= last_px_on_last_row) {
		while (first_px_on_row <= last_px_on_row) {
			func(pixels[first_px_on_row]);
			++first_px_on_row;
		}
		first_px_on_row += start_px.first - end_px.first + w;
		last_px_on_row += w;
	}
}




// Surface

Surface::Surface(SDL_Surface* surf, std::pair<int, int>& f_pixel, std::pair<int, int>& l_pixel) {
	atlas_surface = surf;
	first_pixel = f_pixel;
	last_pixel = l_pixel;
}

inline int Surface::get_w() { return last_pixel.first - first_pixel.first + 1; }
inline int Surface::get_h() { return last_pixel.second - first_pixel.second + 1; }

Uint32 Surface::get_pixel(std::pair<int, int>& px_pos_in_tex) {
	std::pair<int, int> true_px_pos = std::make_pair(px_pos_in_tex.first + first_pixel.first, px_pos_in_tex.second + first_pixel.second);
	return SurfaceUtils::get_pixel_from_surf(atlas_surface, true_px_pos);
}

void Surface::pixel_map(std::pair<int, int>& start_px,
	       		std::pair<int, int>& end_px,
	       		void (*func)(Uint32))
{
	std::pair<int, int> true_start_px(start_px.first + first_pixel.first, start_px.second + first_pixel.second),
			    true_end_px(end_px.first + first_pixel.first, end_px.second + first_pixel.second);
	SurfaceUtils::surf_pixel_map(atlas_surface, true_start_px, true_end_px, func);
}




// SurfaceManager

void SurfaceManager::load_at_init() {
	std::ifstream fin ("metadata/textures_to_load_at_init.json");
	Json::Reader reader;
	Json::Value texture_map;

	reader.parse(fin, texture_map);
	fin.close();

	int num_atlases = texture_map.size();

	std::string filename;
	int file_type;
	SDL_Surface* atlas;
	std::string path_to_images("assets/images/");
	std::string file_ext;
	std::string path;

	for (int i = 0; i < num_atlases; ++i) {
		filename = texture_map[i]["filename"].asString();
		file_type = texture_map[i]["file_type"].asInt();

		if (file_type == 0) {
			file_ext = "png";
			path = path_to_images + file_ext + "/" + filename + "." + file_ext ;
        		atlas = IMG_Load(path.c_str());
		}


        	if (!atlas) {
        		SDL_Log("Couldn't load textures for atlas %s.%s: ", filename, file_ext);
       			continue;
       		}

		atlases.push_back(atlas);
		int num_textures_in_atlas = texture_map[i]["textures"].size();
		std::pair<int, int> f_pixel;
		std::pair<int, int> l_pixel;
		for (int j = 0; j < num_textures_in_atlas; ++j) {
			f_pixel.first = texture_map[i]["textures"][j][0].asInt();
			f_pixel.second = texture_map[i]["textures"][j][1].asInt();
			l_pixel.first = texture_map[i]["textures"][j][2].asInt();
			l_pixel.second = texture_map[i]["textures"][j][3].asInt();

			surfaces.emplace_back(atlas, f_pixel, l_pixel);
		}

	}

}
