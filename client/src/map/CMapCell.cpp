#include "CMapCell.h"

CMapCell::CMapCell() {
	type = EMPTY;
}

CMapCell::CMapCell(CEntity* ent) {
	type = ENTITY;
	this->entity = ent;
}

CMapCell::CMapCell(CBlock* block) {
	type = BLOCK;
	this->block = block;
}

CMapCell* CMapCell::getByChar(char c) {
	auto* cell = new CMapCell();
	if (CBlock::isBlock(c)) {
		cell->type = BLOCK;
		cell->block = CBlock::getBlockBySign(c);
		return cell;
	} else if (c == '0') {
		cell->type = EMPTY;
		return cell;
	} else {
	    cout << "Unknown symbol '" << c << "' in map" << endl;
	    return nullptr;
	}
}