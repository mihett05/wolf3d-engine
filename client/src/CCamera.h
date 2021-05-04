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
    VertexArray* pixels;
	int screenWidth{}, screenHeight{};
	double posX{}, posY{};
	double dirX{}, dirY{};
	double planeX{}, planeY{};

	CMap* map{};
	Clock* clock{};

	void drawEntity();

	double getMoveSpeed();
	double getRotationSpeed();
	bool canMove(bool isForward, CMapCell* cell, CMapCell* cellNext, float diff, double dir) const;
	void moveStraight(bool isForward, double moveSpeed);
public:
	CCamera(Clock* clock, int screenWidth, int screenHeight, CMap* map);
	VertexArray* draw();
};

