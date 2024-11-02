build/debug/DoomPlusPlus: src/main.cpp src/app.h src/app.cpp src/world.h src/world.cpp src/surface_manager.h src/surface_manager.cpp
	g++ -Wall -g -o build/debug/DoomPlusPlus src/main.cpp src/app.cpp src/world.cpp src/surface_manager.cpp -lSDL2main -lSDL2 -lSDL2_image -ljsoncpp
