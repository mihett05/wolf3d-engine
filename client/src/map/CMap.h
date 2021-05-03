#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "CMapCell.h"
#include "../CEntity.h"

const size_t MAP_WIDTH = 32;
const size_t MAP_HEIGHT = 32;

using namespace std;
using namespace sf;


class CMap {
private:
	string fileName;
public:
	Vector2f spawnPosition;
	CMapCell*** map;
	vector<CEntity*>* entities;

	explicit CMap(const string& fileName);
	void tick();
	CEntity* getEntityOn(float x, float y) const;
	~CMap();
};
