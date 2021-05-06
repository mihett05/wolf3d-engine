#ifndef WOLF3D_CBLOCK_H
#define WOLF3D_CBLOCK_H

#include <algorithm>
#include <map>
#include <vector>
#include "../CTexture.h"


using namespace std;

class CBlock {
private:
    char texture;

    static char blocks[];
    static map<char, CBlock*> objects;
public:
    CBlock() = default;
	explicit CBlock(char sign);
	char getTexture() const;

    static CBlock* getBlockBySign(char sign);
	static bool isBlock(char sign);
};

#endif
