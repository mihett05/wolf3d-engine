#ifndef WOLF3D_CBLOCK_H
#define WOLF3D_CBLOCK_H

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../CTexture.h"

using namespace sf;
using namespace std;

class CBlock {
private:
    char texture;

    static char blocks[];
    static map<char, CBlock*> objects;
public:
    CBlock() = default;
	CBlock(char sign);
	char getTexture();

    static CBlock* getBlockBySign(char sign);
	static bool isBlock(char sign);
};

#endif
