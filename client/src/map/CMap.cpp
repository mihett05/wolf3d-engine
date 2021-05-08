#include "CMap.h"
#include <iostream>

CMapCell* CMap::createCell(char sign, int x, int y) {
    CMapCell* cell = nullptr;
    switch (sign) {
        case '0':
            cell = CMapCell::emptyCell;
            break;
        case '@':
            spawnPosition = Vector2f(x, y);
            cell = CMapCell::emptyCell;
            break;
        default:
            if (CBlock::isBlock(sign)) {
                cell = CMapCell::getByChar(sign);
            } else if (CEntity::isEntity(sign)) {
                CEntity* ent = CEntity::getByChar(sign, float(x), float(y));
                if (ent != nullptr)
                    entities->push_back(ent);
                cell = CMapCell::emptyCell;
            }
    }

    if (cell) {
        w = x + 1;
        h = y + 1;
    }

    return cell;
}

CMap::CMap(const string& fileName) : sizeW(MAP_WIDTH), sizeH(MAP_HEIGHT), w(0), h(0), fileName(fileName) {
	entities = new vector<CEntity*>();
	map = new CMapCell*[sizeH * sizeW];

	char* buffer = (char*)calloc(sizeof(char), sizeW);
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Can't open a file " << fileName << endl;
	}
	else {
		for (int y = 0; y < sizeH && !file.eof(); y++) {
			file.getline(buffer, sizeW);
			for (int x = 0; x < sizeW; x++) {
                this->map[y * sizeW + x] = createCell(buffer[x], x, y);
			}
		}
	}
}

CMapCell* CMap::getCellOn(int x, int y) const {
    if ((y >= 0 && y < h) && (x >= 0 && x < w)) {
        return map[y * sizeW + x];
    }
    return nullptr;
}

CEntity* CMap::getEntityOn(float x, float y) const {
	for (auto ent : *entities) {
        Vector2f pos = ent->getPos();
		if (x == pos.x && y == pos.y)
			return ent;
	}
	return nullptr;
}

void CMap::tick() {

}

CMap::~CMap() {
    for (size_t i = 0; i < w; ++i) {
        delete map[i];
    }
    delete[] map;

    entities->clear();
    entities->shrink_to_fit();
}

