#include "CMap.h"
#include <iostream>
#include <fstream>

CMap::CMap(string fileName)
{
	entities = new vector<CEntity*>();
	this->fileName = fileName;
	char buffer[32];
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Not able to open a file " << fileName << endl;
	}
	else
	{
		for (int y = 0; y < 32 && !file.eof(); y++)
		{
			file.getline(buffer, 32);
			for (int x = 0; x < 32; x++)
			{
				CMapCell* cell = CMapCell::getByChar(buffer[x]);
				CEntity* ent = CEntity::getByChar(buffer[x], float(x), float(y));
				if (ent != NULL)
					entities->push_back(ent);
				switch (buffer[x])
				{
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

CEntity* CMap::getEntityOn(float x, float y)
{
	for (size_t i = 0; i < entities->size(); i++)
	{
		CEntity* ent = entities->at(i);
		Vector2f pos = ent->getPos();
		bool isEntityOnPos = x == pos.x && y == pos.y;
		if (isEntityOnPos)
			return ent;
	}
	return NULL;
}

void CMap::tick()
{

}