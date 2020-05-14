#pragma once
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "CMapCell.h"
#include <SFML/Graphics.hpp>

#define mapWidth 32
#define mapHeight 32

using namespace std;
using namespace sf;


class CMap
{
private:
	string fileName;
public:
	Vector2f spawnPosition;
	CMapCell* map[mapHeight][mapWidth];
	CMap(string fileName);
	CMap() = default;
	void tick();
};

