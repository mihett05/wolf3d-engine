#include <SFML/Graphics.hpp>

#include "CGame.h"

int main(int argc, const char* argv[]) {
	CGame game((argc == 2? atoi(argv[1]) : 640), (argc == 3? atoi(argv[2]) : 480), "Engine", 60);
	game.loop();
	return 0;
}