#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "CMap.h"

using namespace std;
using namespace sf;


class CCamera
{
private:
	int screenWidth, screenHeight;
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY;
	CMap map;
	Clock* clock;
	vector<Uint32> texture[8];
public:
	CCamera() = default;
	CCamera(Clock* clock, int screenWidth, int screenHeight, CMap map);
	VertexArray draw();
};

