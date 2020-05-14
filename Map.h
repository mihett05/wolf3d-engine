#pragma once
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

#include "MapCell.h"
#include <SFML/Graphics.hpp>

#define mapWidth 32
#define mapHeight 32

using namespace std;
using namespace sf;


class Map
{
private:
	string fileName;
public:
	Vector2f spawnPosition;
	MapCell* map[mapHeight][mapWidth];
	Map(string fileName);
	Map() = default;
	void tick();
};

