#pragma once
#include "Block.h"
#include "Entity.h"

#define EMPTY 0
#define BLOCK 1
#define ENTITY 2

using namespace std;

class MapCell
{
public:
	int type;
	Entity entity;
	Block block;
	MapCell();
	MapCell(Entity ent);
	MapCell(Block block);
	static MapCell* getByChar(char c);
};





