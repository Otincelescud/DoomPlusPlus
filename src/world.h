#include "app.hpp"

#ifndef World_H
#define World_H

class WorldMap {
public:
	WorldMap(const int w, const int h);
	void init(const char* filename);
	inline short int get_val(std::pair<int, int>& block);
	inline void set_val(std::pair<int, int>& block, short int& val);

private:
	std::vector<std::vector<short int>> block_vals;
};

#endif /* World_H */
