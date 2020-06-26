#include "CMapCell.h"

CMapCell::CMapCell()
{
	type = EMPTY;
}

CMapCell::CMapCell(CEntity ent)
{
	type = ENTITY;
	this->entity = ent;
}

CMapCell::CMapCell(CBlock block)
{
	type = BLOCK;
	this->block = block;
}

CMapCell* CMapCell::getByChar(char c)
{
	CMapCell* cell = new CMapCell();
	map<char, CBlock>::iterator res = CBlock::map.find(c);
	if (res != CBlock::map.end())
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