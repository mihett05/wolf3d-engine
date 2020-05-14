#include "MapCell.h"

MapCell::MapCell()
{
	type = EMPTY;
}

MapCell::MapCell(Entity ent)
{
	type = ENTITY;
	this->entity = ent;
}

MapCell::MapCell(Block block)
{
	type = BLOCK;
	this->block = block;
}

MapCell* MapCell::getByChar(char c)
{
	MapCell* cell = new MapCell();
	map<char, Block>::iterator res = Block::map.find(c);
	if (res != Block::map.end())
	{
		cell->type = BLOCK;
		cell->block = res->second;
		return cell;
	}
	else
	{
		cell->type = EMPTY;
		return cell;
	}
}