#include "CMap.h"
#include <iostream>

CMap::CMap(const string& fileName) {
	entities = new vector<CEntity*>();
	map = new CMapCell**[MAP_HEIGHT];

    for (size_t i = 0; i < MAP_HEIGHT; ++i) {
        map[i] = new CMapCell*[MAP_WIDTH];
    }

	this->fileName = fileName;

	char* buffer = (char*)calloc(sizeof(char), MAP_WIDTH);
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Can't open a file " << fileName << endl;
	}
	else {
		for (int y = 0; y < MAP_HEIGHT && !file.eof(); y++) {
			file.getline(buffer, MAP_WIDTH);
			for (int x = 0; x < MAP_WIDTH; x++) {
			    if (buffer[x] != 0) {
                    switch (buffer[x]) {
                        case '0':
                            this->map[y][x] = CMapCell::emptyCell;
                            break;
                        case '@':
                            spawnPosition = Vector2f(x, y);
                            this->map[y][x] = CMapCell::emptyCell;
                            break;
                        default:
                            if (CBlock::isBlock(buffer[x])) {
                                CMapCell* cell = CMapCell::getByChar(buffer[x]);
                                this->map[y][x] = cell;
                            } else if (CEntity::isEntity(buffer[x])) {
                                CEntity* ent = CEntity::getByChar(buffer[x], float(x), float(y));
                                if (ent != nullptr)
                                    entities->push_back(ent);
                                this->map[y][x] = CMapCell::emptyCell;
                            }
                            break;
                    }
			    }
			}
		}
	}
}

CMapCell* CMap::getCellOn(int x, int y) const {
    if (y < MAP_HEIGHT && x < MAP_WIDTH) {
        return map[y][x];
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
    for (size_t i = 0; i < MAP_HEIGHT; ++i) {
        delete[] map[i];
    }
    delete[] map;

    entities->clear();
    entities->shrink_to_fit();
}


