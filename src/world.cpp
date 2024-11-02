#include "world.h"

WorldMap::WorldMap(const int w, const int h) {
	block_vals.resize(h);
	for (std::vector<short int>& vec: block_vals) vec.resize(w);
}

void WorldMap::init(const char* filename) {
	std::fstream fin (filename, std::ios::in);
	for (std::vector<short int>& row: block_vals) {
		for (short int& block_val: row) {
			fin >> block_val;
			std::cout << block_val << ' ';
		}
		std::cout << '\n';
	}
	fin.close();
}

inline short int WorldMap::get_val(std::pair<int, int>& block) {
	return block_vals[block.second][block.first];
}

inline void WorldMap::set_val(std::pair<int, int>& block, short int& val) {
	block_vals[block.second][block.first] = val;
}
