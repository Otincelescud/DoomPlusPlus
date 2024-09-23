build/debug/DoomPlusPlus: src/main.cpp src/app.hpp src/app.cpp
	g++ -Wall -g -o build/debug/DoomPlusPlus src/main.cpp src/app.cpp -lSDL2main -lSDL2 -lSDL2_image
