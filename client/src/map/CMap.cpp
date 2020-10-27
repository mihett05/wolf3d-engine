#include "CMap.h"
#include <iostream>
#include <fstream>

CMap::CMap(const string& fileName) {
	entities = new vector<CEntity*>();
	map = new CMapCell**[MAP_HEIGHT];

    for (size_t i = 0; i < MAP_HEIGHT; ++i) {
        map[i] = new CMapCell*[MAP_WIDTH];
    }

	this->fileName = fileName;

	char buffer[32];
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Not able to open a file " << fileName << endl;
	}
	else {
		for (int y = 0; y < 32 && !file.eof(); y++) {
			file.getline(buffer, 32);
			for (int x = 0; x < 32; x++) {
				CMapCell* cell = CMapCell::getByChar(buffer[x]);
				CEntity* ent = CEntity::getByChar(buffer[x], float(x), float(y));
				if (ent != nullptr)
					entities->push_back(ent);
				switch (buffer[x]) {
				case '@':
					spawnPosition = Vector2f(x, y);
					break;
				default:
					break;
				}
				this->map[y][x] = cell;
				
			}
		}
	}
}

CEntity* CMap::getEntityOn(float x, float y) const {
	for (auto ent : *entities) {
			Vector2f pos = ent->getPos();
		bool isEntityOnPos = x == pos.x && y == pos.y;
		if (isEntityOnPos)
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
