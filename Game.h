#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Entity.h"
#include "Camera.h"
#include "Map.h"

#define mapWidth 24
#define mapHeight 24

using namespace sf;
using namespace std;

class Game
{
protected:
	unique_ptr<RenderWindow> window;
	Event event;
	Player player;
	Clock clock;
	Camera camera;
	Map map;
	vector<Entity> entities;
	
public:
	Game(unsigned int width, unsigned int height, string title, unsigned int frameLimit);
	void draw();
	void update();
	void loop();
	void destroy();
};

