#pragma once
#include <iostream>
#include "CBlock.h"
#include "../CEntity.h"

#define EMPTY 0
#define BLOCK 1
#define ENTITY 2

using namespace std;

class CMapCell {
public:
	int type;
	CBlock* block;

	CMapCell();
	explicit CMapCell(CEntity* ent);
	explicit CMapCell(CBlock* block);

	static CMapCell* emptyCell;
	static CMapCell* getByChar(char c);
};





