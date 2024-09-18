main.cpp:
	g++ -o build/debug/DoomPlusPlus src/main.cpp src/app.cpp -lSDL2main $(pkg-config --cflags --libs  sdl2 SDL2_mixer SDL2_image)
