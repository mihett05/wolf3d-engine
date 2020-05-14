#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace std;
using namespace sf;


class Camera
{
private:
	int screenWidth, screenHeight;
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY;
	Map map;
	Clock* clock;
	vector<Uint32> texture[8];
public:
	Camera() = default;
	Camera(Clock* clock, int screenWidth, int screenHeight, Map map);
	VertexArray draw();
};

