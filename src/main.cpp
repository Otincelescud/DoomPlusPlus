#ifdef _WIN32 || _WIN64
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#endif

#include <SDL2/SDL.h>

void start_app() {

}

#ifdef __linux__
int main(int argc, char *argv[]) {
	start_app();	

	return 0;
}
#elif __WIN32 || __WIN64
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	start_app();

	return 0;
}
#endif
