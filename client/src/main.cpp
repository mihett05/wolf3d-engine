#include <iostream>

#include <SDL2/SDL.h>
#include "CGame.h"



using namespace std;

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Can't init SDL: " << SDL_GetError() << endl;
    }
    if (IMG_Init(IMG_INIT_PNG)) {
        cout << "Can't init SDL_image: " << SDL_GetError() << endl;
    }

	CGame game((argc == 2? atoi(argv[1]) : 640), (argc == 3? atoi(argv[2]) : 480), "Engine", 60);
	game.loop();

	SDL_Quit();
	return 0;
}