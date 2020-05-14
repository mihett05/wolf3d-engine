#include <SFML/Graphics.hpp>

#include "Game.h"

int main(int argc, char* argv)
{
	
	Game game(640, 480, "Engine", 60);
	game.loop();
	return 0;
}