#include "CMapCell.h"

CMapCell::CMapCell() {
	type = EMPTY;
}

CMapCell::CMapCell(CBlock* block) {
	type = BLOCK;
	this->block = block;
}

CMapCell* CMapCell::emptyCell = new CMapCell();

CMapCell* CMapCell::getByChar(char c) {
    if (c == '0') {
        return CMapCell::emptyCell;
    } else if (CBlock::isBlock(c)) {
        CMapCell* cell = new CMapCell();
		cell->type = BLOCK;
		cell->block = CBlock::getBlockBySign(c);
		return cell;
	} else {
	    cout << "Unknown symbol '" << c << "' in map" << endl;
	    return nullptr;
	}
}