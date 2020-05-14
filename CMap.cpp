#include "CMap.h"
#include <iostream>
#include <fstream>

CMap::CMap(string fileName)
{
	this->fileName = fileName;
	char buffer[32];
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Not able to open a file " << fileName << endl;
	}
	else
	{
		for (size_t y = 0; y < 32 && !file.eof(); y++)
		{
			file.getline(buffer, 32);
			for (size_t x = 0; x < 32; x++)
			{
				CMapCell* cell = CMapCell::getByChar(buffer[x]);
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

void CMap::tick()
{

}