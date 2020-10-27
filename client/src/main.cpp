#include <SFML/Graphics.hpp>

#include "CGame.h"

int main(int argc, char** argv) {
	
	CGame game(1920, 1080, "Engine", 60);
	game.loop();
	return 0;
}