#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "CMapCell.h"
#include "CEntity.h"

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
	vector<CEntity*>* entities;

	CMap(string fileName);
	CMap() = default;
	void tick();
	CEntity* getEntityOn(float x, float y);
};

