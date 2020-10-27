#pragma once
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "./map/CMap.h"
#include "./map/CMapCell.h"

using namespace std;
using namespace sf;


class CCamera {
private:
	int screenWidth{}, screenHeight{};
	double posX{}, posY{};
	double dirX{}, dirY{};
	double planeX{}, planeY{};
	CMap* map{};
	Clock* clock{};
	vector<Uint32> texture[32];
public:
	CCamera() = default;
	CCamera(Clock* clock, int screenWidth, int screenHeight, CMap* map);
	VertexArray draw();
};

