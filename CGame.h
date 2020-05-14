#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "CEntity.h"
#include "CCamera.h"
#include "CMap.h"

#define mapWidth 24
#define mapHeight 24

using namespace sf;
using namespace std;

class CGame
{
protected:
	unique_ptr<RenderWindow> window;
	Event event;
	Clock clock;
	CCamera camera;
	CMap map;
	vector<CEntity> entities;
	
public:
	CGame(unsigned int width, unsigned int height, string title, unsigned int frameLimit);
	void draw();
	void update();
	void loop();
	void destroy();
};

